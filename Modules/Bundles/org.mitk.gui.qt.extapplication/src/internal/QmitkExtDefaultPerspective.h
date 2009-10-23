/*=========================================================================

 Program:   Medical Imaging & Interaction Toolkit
 Language:  C++
 Date:      $Date$
 Version:   $Revision$

 Copyright (c) German Cancer Research Center, Division of Medical and
 Biological Informatics. All rights reserved.
 See MITKCopyright.txt or http://www.mitk.org/copyright.html for details.

 This software is distributed WITHOUT ANY WARRANTY; without even
 the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 PURPOSE.  See the above copyright notices for more information.

 =========================================================================*/


#ifndef QMITKEXTDEFAULTPERSPECTIVE_H_
#define QMITKEXTDEFAULTPERSPECTIVE_H_

#include <cherryIPerspectiveFactory.h>

struct QmitkExtDefaultPerspective : public cherry::IPerspectiveFactory
{

  void CreateInitialLayout(cherry::IPageLayout::Pointer layout);

};

#endif /* QMITKEXTDEFAULTPERSPECTIVE_H_ */