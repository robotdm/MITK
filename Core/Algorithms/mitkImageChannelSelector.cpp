#include "mitkImageChannelSelector.h"

//##ModelId=3E1B1980039C
mitk::ImageChannelSelector::ImageChannelSelector() : m_ChannelNr(0)
{
}


//##ModelId=3E1B198003B0
mitk::ImageChannelSelector::~ImageChannelSelector()
{
}

//##ModelId=3E3BD0C70343
void mitk::ImageChannelSelector::GenerateOutputInformation()
{
  mitk::Image::ConstPointer input  = this->GetInput();
  mitk::Image::Pointer output = this->GetOutput();

  itkDebugMacro(<<"GenerateOutputInformation()");

  output->Initialize(input->GetPixelType(), input->GetDimension(), input->GetDimensions());

  // initialize geometry
  output->SetPropertyList(input->GetPropertyList()->Clone());  
	output->SetGeometry(input->GetGeometry());
}

//##ModelId=3E3BD0C903DC
void mitk::ImageChannelSelector::GenerateData()
{
  const Image::RegionType& requestedRegion = GetOutput()->GetRequestedRegion();

  //do we really need the complete channel?
  if(requestedRegion.GetSize(3)>1)
    SetChannelItem(GetChannelData(m_ChannelNr), 0);
  else
  //or only a complete volume at a time?
  if(requestedRegion.GetSize(2)>1)
    SetVolumeItem(GetVolumeData(requestedRegion.GetIndex(3), m_ChannelNr), requestedRegion.GetIndex(3), 0);
  else
  //not even a complete volume, so now take just a slice!
    SetSliceItem(GetSliceData(requestedRegion.GetIndex(2), requestedRegion.GetIndex(3), m_ChannelNr), requestedRegion.GetIndex(2), requestedRegion.GetIndex(3), 0);
}

void mitk::ImageChannelSelector::GenerateInputRequestedRegion()
{
  Superclass::GenerateInputRequestedRegion();

  mitk::ImageToImageFilter::InputImagePointer input =
    const_cast< mitk::ImageToImageFilter::InputImageType * > ( this->GetInput() );
  mitk::Image::Pointer output = this->GetOutput();

  Image::RegionType requestedRegion;
  requestedRegion = output->GetRequestedRegion();
  requestedRegion.SetIndex(4, m_ChannelNr);
  requestedRegion.SetSize(4, 1);

  input->SetRequestedRegion( & requestedRegion );
}


