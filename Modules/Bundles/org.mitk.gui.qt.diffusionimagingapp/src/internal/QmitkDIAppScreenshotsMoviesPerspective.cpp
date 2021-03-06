/*=========================================================================
 
 Program:   BlueBerry Platform
 Language:  C++
 Date:      $Date: 2009-10-23 02:59:36 +0200 (Fr, 23 Okt 2009) $
 Version:   $Revision: 19652 $
 
 Copyright (c) German Cancer Research Center, Division of Medical and
 Biological Informatics. All rights reserved.
 See MITKCopyright.txt or http://www.mitk.org/copyright.html for details.
 
 This software is distributed WITHOUT ANY WARRANTY; without even
 the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 PURPOSE.  See the above copyright notices for more information.
 
 =========================================================================*/

#include "QmitkDIAppScreenshotsMoviesPerspective.h"
#include "berryIViewLayout.h"

void QmitkDIAppScreenshotsMoviesPerspective::CreateInitialLayout(berry::IPageLayout::Pointer layout)
{
  /////////////////////////////////////////////////////
  // all di-app perspectives should have the following:
  /////////////////////////////////////////////////////

  std::string editorArea = layout->GetEditorArea();

  layout->AddStandaloneView("org.mitk.views.datamanager",
    false, berry::IPageLayout::LEFT, 0.3f, editorArea);

  layout->AddStandaloneView("org.mitk.views.controlvisualizationpropertiesview",
    false, berry::IPageLayout::BOTTOM, .2f, "org.mitk.views.datamanager");

  berry::IFolderLayout::Pointer left =
    layout->CreateFolder("org.mbi.diffusionimaginginternal.leftcontrols",
    berry::IPageLayout::BOTTOM, 0.15f, "org.mitk.views.controlvisualizationpropertiesview");

  layout->AddStandaloneView("org.mitk.views.imagenavigator",
    false, berry::IPageLayout::BOTTOM, .4f, "org.mbi.diffusionimaginginternal.leftcontrols");

  /////////////////////////////////////////////
  // here goes the perspective specific stuff
  /////////////////////////////////////////////

  left->AddView("org.mitk.views.screenshotmaker");
  berry::IViewLayout::Pointer lo = layout->GetViewLayout("org.mitk.views.screenshotmaker");
  lo->SetCloseable(false);

  left->AddView("org.mitk.views.moviemaker");
  lo = layout->GetViewLayout("org.mitk.views.moviemaker");
  lo->SetCloseable(false);

}
