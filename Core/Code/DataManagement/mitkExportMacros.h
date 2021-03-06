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


#ifndef MITKEXPORTMACROS_H
#define MITKEXPORTMACROS_H

/**
  * Macros for import/export declarations
  */
#if defined(WIN32)
  #define MITK_EXPORT __declspec(dllexport)
  #define MITK_IMPORT __declspec(dllimport)
  #define MITK_LOCAL
#else
  #if __GNUC__ >= 4
    #define MITK_EXPORT __attribute__ ((visibility ("default")))
    #define MITK_IMPORT __attribute__ ((visibility ("default")))
    #define MITK_LOCAL  __attribute__ ((visibility ("hidden")))
  #else
    #define MITK_EXPORT
    #define MITK_IMPORT
    #define MITK_LOCAL
  #endif
#endif

#endif // MITKEXPORTMACROS_H
