/*=========================================================================

  Library:   CTK

  Copyright (c) Kitware Inc.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.commontk.org/LICENSE

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

=========================================================================*/

#ifndef __ctkVTKScalarsToColorsUtils_h
#define __ctkVTKScalarsToColorsUtils_h

// CTK includes
#include "ctkVisualizationVTKWidgetsExport.h"

// VTK includes
class vtkScalarsToColors;

namespace ctk {
///
/// \ingroup vtkWidgets
/// Convert a vtkScalarsToColors into a QImage
/// If size is empty, it will use the large icon size of the application style
QImage CTK_VISUALIZATION_VTK_WIDGETS_EXPORT scalarsToColorsImage(vtkScalarsToColors* scalarsToColors, const QSize& size = QSize());

///
/// \ingroup vtkWidgets
/// Create a base 64 image tag. Can be used that way:
/// QString("<img src=\"%1\">").arg(base64HTMLImageTagSrc(myImage);
QString CTK_VISUALIZATION_VTK_WIDGETS_EXPORT base64HTMLImageTagSrc(const QImage& image);

}

#endif
