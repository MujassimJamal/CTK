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

// QT includes
#include <QApplication>
#include <QLabel>
#include <QTimer>

// CTK includes
#include "ctkWidgetsUtils.h"
#include "ctkLogo-small-transparent.h"

// STD includes
#include <cstdlib>
#include <iostream>

//-----------------------------------------------------------------------------
int ctkWidgetsUtilsTest1(int argc, char * argv [] )
{
  QApplication app(argc, argv);

  QImage image = ctk::kwIconToQImage(image_ctkLogo_small_transparent,
    image_ctkLogo_small_transparent_width, image_ctkLogo_small_transparent_height,
    image_ctkLogo_small_transparent_pixel_size, image_ctkLogo_small_transparent_length);

  QLabel label;
  label.setPixmap(QPixmap::fromImage(image));
  label.show();

  if (argc < 2 || QString(argv[1]) != "-I")
    {
    QTimer::singleShot(200, &app, SLOT(quit()));
    }
  return app.exec();
}
