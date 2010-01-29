/*=========================================================================

 Program:   BlueBerry Platform
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

#ifndef BERRYIMENUITEM_H_
#define BERRYIMENUITEM_H_

#include <osgi/framework/Object.h>
#include <osgi/framework/Macros.h>

#include "../berryUiDll.h"
#include "berryUIElement.h"

namespace berry
{

struct IMenu;
struct ImageDescriptor;
struct IMenuItemListener;

/**
 * Instances of this class represent a selectable user interface object
 * that issues notification when pressed and released.
 * <dl>
 * <dt><b>Styles:</b></dt>
 * <dd>CHECK, CASCADE, PUSH, RADIO, SEPARATOR</dd>
 * </dl>
 * <p>
 * Note: Only one of the styles CHECK, CASCADE, PUSH, RADIO and SEPARATOR
 * may be specified.
 * </p>
 */
struct BERRY_UI IMenuItem: public UIElement
{

protected:

  IMenuItem(SmartPointer<IServiceLocator> locator) :
    UIElement(locator)
  {
  }

public:

  osgiObjectMacro(berry::IMenuItem)
  osgiManifestMacro(IMenuItem)

  static const std::string TEXT;
  static const std::string IMAGE;

  virtual void SetMenu(SmartPointer<IMenu> ) = 0;

};

}

#endif /* BERRYIMENUITEM_H_ */