#include "version.h"

namespace libredwg2 {

////////////////////////////////////////////////////////////////

Version::Version() :
release_(Unknown),
version_(0)
{
}

////////////////////////////////////////////////////////////////

Version::Version(Release release, size_t maintenance) :
release_(release),
version_(maintenance)
{
}

////////////////////////////////////////////////////////////////

bool Version::equals(Release release) const
{
  return release_ == release;
}

////////////////////////////////////////////////////////////////

bool Version::isAtLeast(Release release, size_t maintenance) const
{
  if (release_ > release)
    return true;
  else if (release_ < release)
    return false;
  else
    return version_ >= maintenance;
}

////////////////////////////////////////////////////////////////

bool Version::isBetween(Release min, Release max) const
{
  if (release_ < min)
    return false;
  return release_ <= max;
}

////////////////////////////////////////////////////////////////

bool Version::isGreaterThan(Release release, size_t maintenance) const
{
  if (release_ > release)
    return true;
  else if (release_ < release)
    return false;
  else
    return version_ > maintenance;
}

////////////////////////////////////////////////////////////////

void Version::setMaintenance(size_t maintenance)
{
  version_ = maintenance;
}

////////////////////////////////////////////////////////////////

void Version::setRelease(Release release)
{
  release_ = release;
}

////////////////////////////////////////////////////////////////

}
