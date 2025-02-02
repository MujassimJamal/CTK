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
#include <QCoreApplication>
#include <QProcess>

// STD includes
#include <cstdlib>
#include <iostream>

int ctkDICOMDemoSCUTest1(int argc, char * argv [])
{
  QCoreApplication app(argc, argv);

  QStringList arguments = app.arguments();
  QString testName = arguments.takeFirst();

  if (arguments.count() != 1)
    {
    std::cerr << "Usage: " << qPrintable(testName)
              << " <path-to-ctkDICOMDemoSCU-executable>" << std::endl;
    return EXIT_FAILURE;
    }

  QString command = arguments.at(0);

  QString peer("www.dicomserver.co.uk");
  QString port("104");
  QString aeTitle("MOVESCP");
  QStringList parameters;
  parameters << peer << port << aeTitle;

  std::cout << "Testing:\n"
            << qPrintable(command) << " "
            << qPrintable(parameters.join(" ")) << std::endl;

  int res = QProcess::execute(command, parameters);
  if (res != EXIT_SUCCESS)
    {
    std::cerr << '\"' << qPrintable(command) << '\"'
              << " returned " << res << std::endl;
    return res;
    }
  return res;
}
