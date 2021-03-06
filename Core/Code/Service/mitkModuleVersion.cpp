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

#include "mitkModuleVersion.h"

#include <vector>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <cctype>

namespace mitk {

const char ModuleVersion::SEPARATOR = '.';

bool IsInvalidQualifier(char c)
{
  return !(std::isalnum(c) || c == '_' || c == '-');
}

ModuleVersion ModuleVersion::EmptyVersion()
{
  static ModuleVersion emptyV(false);
  return emptyV;
}

ModuleVersion ModuleVersion::UndefinedVersion()
{
  static ModuleVersion undefinedV(true);
  return undefinedV;
}

ModuleVersion& ModuleVersion::operator=(const ModuleVersion& v)
{
  majorVersion = v.majorVersion;
  minorVersion = v.minorVersion;
  microVersion = v.microVersion;
  qualifier = v.qualifier;
  undefined = v.undefined;
  return *this;
}

ModuleVersion::ModuleVersion(bool undefined)
  : majorVersion(0), minorVersion(0), microVersion(0), qualifier(""), undefined(undefined)
{

}

void ModuleVersion::Validate()
{
  if (std::find_if(qualifier.begin(), qualifier.end(), IsInvalidQualifier) != qualifier.end())
    throw std::invalid_argument(std::string("invalid qualifier: ") + qualifier);

  undefined = false;
}

ModuleVersion::ModuleVersion(unsigned int majorVersion, unsigned int minorVersion, unsigned int microVersion)
  : majorVersion(majorVersion), minorVersion(minorVersion), microVersion(microVersion), qualifier(""),
    undefined(false)
{

}

ModuleVersion::ModuleVersion(unsigned int majorVersion, unsigned int minorVersion, unsigned int microVersion, const std::string& qualifier)
   : majorVersion(majorVersion), minorVersion(minorVersion), microVersion(microVersion), qualifier(qualifier),
     undefined(true)
{
  this->Validate();
}

ModuleVersion::ModuleVersion(const std::string& version)
  : majorVersion(0), minorVersion(0), microVersion(0), undefined(true)
{
  unsigned int maj = 0;
  unsigned int min = 0;
  unsigned int mic = 0;
  std::string qual("");

  std::vector<std::string> st;
  std::stringstream ss(version);
  std::string token;
  while(std::getline(ss, token, SEPARATOR))
  {
    st.push_back(token);
  }

  if (st.empty()) return;

  bool ok = true;
  ss.clear();
  ss.str(st[0]);
  ss >> maj;
  ok = !ss.fail();

  if (st.size() > 1)
  {
    ss.clear();
    ss.str(st[1]);
    ss >> min;
    ok = !ss.fail();
    if (st.size() > 2)
    {
      ss.clear();
      ss.str(st[2]);
      ss >> mic;
      ok = !ss.fail();
      if (st.size() > 3)
      {
        qual = st[3];
        if (st.size() > 4)
        {
           ok = false;
        }
      }
    }
  }

  if (!ok) throw std::invalid_argument("invalid format");

  majorVersion = maj;
  minorVersion = min;
  microVersion = mic;
  qualifier = qual;
  this->Validate();
}

ModuleVersion::ModuleVersion(const ModuleVersion& version)
: majorVersion(version.majorVersion), minorVersion(version.minorVersion),
  microVersion(version.microVersion), qualifier(version.qualifier),
  undefined(version.undefined)
{

}

ModuleVersion ModuleVersion::ParseVersion(const std::string& version)
{
  if (version.empty())
  {
    return EmptyVersion();
  }

  std::string version2(version);
  version2.erase(0, version2.find_first_not_of(' '));
  version2.erase(version2.find_last_not_of(' ')+1);
  if (version2.empty())
  {
    return EmptyVersion();
  }

  return ModuleVersion(version2);
}

bool ModuleVersion::IsUndefined() const
{
  return undefined;
}

unsigned int ModuleVersion::GetMajor() const
{
  if (undefined) throw std::logic_error("Version undefined");
  return majorVersion;
}

unsigned int ModuleVersion::GetMinor() const
{
  if (undefined) throw std::logic_error("Version undefined");
  return minorVersion;
}

unsigned int ModuleVersion::GetMicro() const
{
  if (undefined) throw std::logic_error("Version undefined");
  return microVersion;
}

std::string ModuleVersion::GetQualifier() const
{
  if (undefined) throw std::logic_error("Version undefined");
  return qualifier;
}

std::string ModuleVersion::ToString() const
{
  if (undefined) return "undefined";

  std::string result;
  std::stringstream ss(result);
  ss << majorVersion << SEPARATOR << minorVersion << SEPARATOR << microVersion;
  if (!qualifier.empty())
  {
    ss << SEPARATOR << qualifier;
  }
  return result;
}

bool ModuleVersion::operator==(const ModuleVersion& other) const
{
  if (&other == this)
  { // quicktest
    return true;
  }

  if (other.undefined && this->undefined) return true;
  if (this->undefined) throw std::logic_error("Version undefined");
  if (other.undefined) return false;

  return (majorVersion == other.majorVersion) && (minorVersion == other.minorVersion) && (microVersion
      == other.microVersion) && qualifier == other.qualifier;
}

int ModuleVersion::Compare(const ModuleVersion& other) const
{
  if (&other == this)
  { // quicktest
    return 0;
  }

  if (this->undefined || other.undefined)
    throw std::logic_error("Cannot compare undefined version");

  if (majorVersion < other.majorVersion)
  {
    return -1;
  }

  if (majorVersion == other.majorVersion)
  {

    if (minorVersion < other.minorVersion)
    {
      return -1;
    }

    if (minorVersion == other.minorVersion)
    {

      if (microVersion < other.microVersion)
      {
        return -1;
      }

      if (microVersion == other.microVersion)
      {
        return qualifier.compare(other.qualifier);
      }
    }
  }
  return 1;
}

}

std::ostream& operator<<(std::ostream& os, const mitk::ModuleVersion& v)
{
  return os << v.ToString();
}
