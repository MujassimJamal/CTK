/*=========================================================================

  Library:   CTK

  Copyright (c) Kitware Inc.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0.txt

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

=========================================================================*/

// Qt includes
#include <QApplication>
#include <QDir>
#include <QTimer>

// ctk includes
#include "ctkCoreTestingMacros.h"
#include "ctkUtils.h"

// ctkDICOMCore includes
#include "ctkDICOMDatabase.h"

// ctkDICOMWidget includes
#include "ctkDICOMBrowser.h"

// STD includes
#include <iostream>

int ctkDICOMBrowserTest1( int argc, char * argv [] )
{
  QApplication app(argc, argv);

  QStringList arguments = app.arguments();
  QString testName = arguments.takeFirst();

  bool interactive = arguments.removeOne("-I");

  if (arguments.count() != 1)
    {
    std::cerr << "Usage: " << qPrintable(testName)
              << " [-I] <path-to-dicom-directory>" << std::endl;
    return EXIT_FAILURE;
    }

  QString dicomDirectory(arguments.at(0));

  QFileInfo tempFileInfo(QDir::tempPath() + QString("/ctkDICOMBrowserTest1-db"));
  QString dbDir = tempFileInfo.absoluteFilePath();
  qDebug().noquote() << "\n\n" << testName << ": Using directory: " << dbDir;
  if (tempFileInfo.exists())
    {
    qDebug().noquote() << "\n\n" << testName << ": Removing directory: " << dbDir;
    ctk::removeDirRecursively(dbDir);
    }
  qDebug().noquote() << "\n\n" << testName << ": Making directory: " << dbDir;
  QDir dir(dbDir);
  dir.mkdir(dbDir);

  ctkDICOMBrowser browser;
  browser.setDatabaseDirectory(dbDir);

  browser.show();

  browser.setDisplayImportSummary(false);
  qDebug().noquote() << testName << ": Importing directory " << dicomDirectory;

  // [Deprecated]
  // make sure copy/link dialog doesn't pop up, always copy on import
  /*
  QSettings settings;
  QString settingsString = settings.value("MainWindow/DontConfirmCopyOnImport").toString();
  settings.setValue("MainWindow/DontConfirmCopyOnImport", QString("0")); // QMessageBox::AcceptRole
  CHECK_INT(browser.importDirectoryMode(), static_cast<int>(ctkDICOMBrowser::ImportDirectoryCopy));
  */
  // [/Deprecated]

  // Test import of a few specific files
  QDirIterator it(dicomDirectory, QStringList() << "*.IMA", QDir::Files, QDirIterator::Subdirectories);
  // Skip a few files
  it.next();
  it.next();
  // Add 3 files
  QStringList files;
  files << it.next();
  files << it.next();
  files << it.next();
  browser.importFiles(files);
  browser.waitForImportFinished();

  qDebug().noquote() << testName << ":"
    << " " << browser.patientsAddedDuringImport()
    << " " << browser.studiesAddedDuringImport()
    << " " << browser.seriesAddedDuringImport()
    << " " << browser.instancesAddedDuringImport();

  CHECK_INT(browser.patientsAddedDuringImport(), 1);
  CHECK_INT(browser.studiesAddedDuringImport(), 1);
  CHECK_INT(browser.seriesAddedDuringImport(), 1);
  CHECK_INT(browser.instancesAddedDuringImport(), 3);

  browser.importDirectories(QStringList() << dicomDirectory);
  browser.waitForImportFinished();

  qDebug().noquote() << "\n\n" << testName << ": Added to database directory: " << files;

  // [Deprecated]
  // reset to the original copy/import setting
  //settings.setValue("MainWindow/DontConfirmCopyOnImport", settingsString);
  // [/Deprecated]

  CHECK_INT(browser.patientsAddedDuringImport(), 1);
  CHECK_INT(browser.studiesAddedDuringImport(), 1);
  CHECK_INT(browser.seriesAddedDuringImport(), 1);
  CHECK_INT(browser.instancesAddedDuringImport(), 100);

  qDebug().noquote() << "\n\n" << testName << ": Added to database directory: " << dbDir;

  if (!interactive)
    {
    QTimer::singleShot(200, &app, SLOT(quit()));
    }

  return app.exec();
}
