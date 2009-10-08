/*=========================================================================
 
 Program:   openCherry Platform
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

#include "cherryJobChangeEvent.h"
#include "../cherryJob.h"

namespace cherry
{

JobChangeEvent::JobChangeEvent() :
  delay(-1), reschedule(false)
{
}

Poco::Timestamp::TimeDiff JobChangeEvent::GetDelay() const
{
  return delay;
}

Job::Pointer JobChangeEvent::GetJob() const
{
  return job;
}

IStatus::Pointer JobChangeEvent::GetResult() const
{
  return result;
}

}