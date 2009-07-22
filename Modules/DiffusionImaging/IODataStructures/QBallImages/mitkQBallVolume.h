/*=========================================================================

Program:   Medical Imaging & Interaction Toolkit
Module:    $RCSfile$
Language:  C++
Date:      $Date: 2008-02-07 17:17:57 +0100 (Do, 07 Feb 2008) $
Version:   $Revision: 11989 $

Copyright (c) German Cancer Research Center, Division of Medical and
Biological Informatics. All rights reserved.
See MITKCopyright.txt or http://www.mitk.org/copyright.html for details.

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the above copyright notices for more information.

=========================================================================*/


#ifndef __mitkDiffusionVolumes__h
#define __mitkDiffusionVolumes__h

#include "mitkBaseData.h"
#include "itkVectorImage.h"

namespace mitk 
{

  /**
  * \brief this class encapsulates diffusion volumes (vectorimages not
  * yet supported by mitkImage)
  */
  template<class TPixelType>
  class DiffusionVolumes : public BaseData
  {

  public:

    typedef typename itk::VectorImage<TPixelType, 3> ImageType;
    typedef vnl_vector_fixed< double, 3 >      GradientDirectionType;
    typedef itk::VectorContainer< unsigned int, 
      GradientDirectionType >                  GradientDirectionContainerType;

    mitkClassMacro( DiffusionVolumes, BaseData );
    itkNewMacro(Self);

    void SetRequestedRegionToLargestPossibleRegion();
    bool RequestedRegionIsOutsideOfTheBufferedRegion();
    virtual bool VerifyRequestedRegion();
    void SetRequestedRegion(itk::DataObject *data);

    void AverageRedundantGradients();

    void DuplicateIfSingleSlice();

    typename ImageType::Pointer GetImage()
    { return m_Image; }
    void SetImage(typename ImageType::Pointer image )
    { this->m_Image = image; }

    GradientDirectionContainerType::Pointer GetDirections()
    { return m_Directions; }
    void SetDirections( GradientDirectionContainerType::Pointer directions )
    { this->m_Directions = directions; }

    itkGetMacro(B_Value, float);
    itkSetMacro(B_Value, float);

  protected:
    DiffusionVolumes();
    virtual ~DiffusionVolumes();

    typename ImageType::Pointer m_Image;

    GradientDirectionContainerType::Pointer m_Directions;

    float m_B_Value;

  };

} // namespace mitk

#include "mitkDiffusionVolumes.txx"

#endif /* __mitkDiffusionVolumes__h */