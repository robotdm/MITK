/*=========================================================================

Program:   Medical Imaging & Interaction Toolkit
Module:    $RCSfile: QmitkTrackingDeviceWidget.cpp $
Language:  C++
Date:      $Date: 2009-05-12 19:14:45 +0200 (Di, 12 Mai 2009) $
Version:   $Revision: 1.12 $

Copyright (c) German Cancer Research Center, Division of Medical and
Biological Informatics. All rights reserved.
See MITKCopyright.txt or http://www.mitk.org/copyright.html for details.

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#include "QmitkTrackingDeviceConfigurationWidget.h"



QmitkTrackingDeviceConfigurationWidget::QmitkTrackingDeviceConfigurationWidget(QWidget* parent, Qt::WindowFlags f)
  : QWidget(parent, f)
{
}


QmitkTrackingDeviceConfigurationWidget::~QmitkTrackingDeviceConfigurationWidget()
{
}

void QmitkTrackingDeviceConfigurationWidget::CreateQtPartControl(QWidget *parent)
{
  if (!m_Controls)
  {
  // create GUI widgets
  m_Controls = new Ui::QmitkTrackingDeviceConfigurationWidgetControls;
  m_Controls->setupUi(parent);
  }
}