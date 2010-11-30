#include <mitkWiiMoteAllDataEvent.h>

#include <mitkInteractionConst.h>

mitk::WiiMoteAllDataEvent::WiiMoteAllDataEvent
(int eventType
 , float pitchSpeed
 , float rollSpeed
 , float yawSpeed
 , float orientationX
 , float orientationY
 , float orientationZ
 , float roll
 , float pitch)
: Event(NULL, eventType, mitk::BS_NoButton, mitk::BS_NoButton, Key_none)
, m_IRDotRawX(0) 
, m_IRDotRawY(0)
, m_Button(0)
, m_PitchSpeed(pitchSpeed)
, m_RollSpeed(rollSpeed)
, m_YawSpeed(yawSpeed)
, m_OrientationX(orientationX)
, m_OrientationY(orientationY)
, m_OrientationZ(orientationZ)
, m_Roll(roll)
, m_Pitch(pitch)
{
}

mitk::WiiMoteAllDataEvent::~WiiMoteAllDataEvent()
{
}

void mitk::WiiMoteAllDataEvent::SetIRDotRawX(float xCoordinate)
{
  this->m_IRDotRawX = xCoordinate;
}

float mitk::WiiMoteAllDataEvent::GetIRDotRawY() const
{
  return this-> m_IRDotRawX;
}

void mitk::WiiMoteAllDataEvent::SetIRDotRawY(float yCoordinate)
{
  this->m_IRDotRawY = yCoordinate;
}

float mitk::WiiMoteAllDataEvent::GetIRDotRawX() const
{
  return this->m_IRDotRawY;
}

void mitk::WiiMoteAllDataEvent::SetButton(int button)
{
  this->m_Button = button;
}

int mitk::WiiMoteAllDataEvent::GetButton() const
{
  return this->m_Button;
}

void mitk::WiiMoteAllDataEvent::SetPitchSpeed(float pitchSpeed)
{
  this->m_PitchSpeed = pitchSpeed;
}

float mitk::WiiMoteAllDataEvent::GetPitchSpeed() const
{
  return this->m_PitchSpeed;
}

void mitk::WiiMoteAllDataEvent::SetRollSpeed(float rollSpeed)
{
  this->m_RollSpeed = rollSpeed;
}

float mitk::WiiMoteAllDataEvent::GetRollSpeed() const
{
  return this->m_RollSpeed;
}

void mitk::WiiMoteAllDataEvent::SetYawSpeed(float yawSpeed)
{
  this->m_YawSpeed = yawSpeed;
}

float mitk::WiiMoteAllDataEvent::GetYawSpeed() const
{
  return this->m_YawSpeed;
}

void mitk::WiiMoteAllDataEvent::SetOrientationX(float orientationX)
{
  this->m_OrientationX = orientationX;
}

float mitk::WiiMoteAllDataEvent::GetOrientationX() const
{
  return this->m_OrientationX;
}

void mitk::WiiMoteAllDataEvent::SetOrientationY(float orientationY)
{
  this->m_OrientationY = orientationY;
}

float mitk::WiiMoteAllDataEvent::GetOrientationY() const
{
  return this->m_OrientationY;
}

void mitk::WiiMoteAllDataEvent::SetOrientationZ(float orientationZ)
{
  this->m_OrientationZ = orientationZ;
}

float mitk::WiiMoteAllDataEvent::GetOrientationZ() const
{
  return this->m_OrientationZ;
}

void mitk::WiiMoteAllDataEvent::SetRoll(float roll)
{
  this->m_Roll = roll;
}

float mitk::WiiMoteAllDataEvent::GetRoll() const
{
  return this->m_Roll;
}

void mitk::WiiMoteAllDataEvent::SetPitch(float pitch)
{
  this->m_Pitch = pitch;
}

float mitk::WiiMoteAllDataEvent::GetPitch() const
{
  return this->m_Pitch;
}

// ------------------------- itk::EventObject Implementation -----------------------
const char* mitk::WiiMoteAllDataEvent::GetEventName() const
{ 
  return "WiiMoteAllDataEvent"; 
} 

bool mitk::WiiMoteAllDataEvent::CheckEvent(const itk::EventObject *e) const
{ 
  return dynamic_cast<const Self*>(e); 
} 

itk::EventObject* mitk::WiiMoteAllDataEvent::MakeObject() const
{ 
  return new Self
    (this->GetType()
    ,this->GetPitchSpeed()
    ,this->GetRollSpeed()
    ,this->GetYawSpeed()
    ,this->GetOrientationX()
    ,this->GetOrientationY()
    ,this->GetOrientationZ()
    ,this->GetRoll()
    ,this->GetPitch()); 
} 

