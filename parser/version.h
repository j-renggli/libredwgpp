#pragma once

#include <includes.h>

namespace libredwg2 {

class Version
{
  ////////////////////////////////////////////////////////////////
  // Definitions
  ////////////////////////////////////////////////////////////////
  public:
    enum Release {
      R13,
      R14,
      R2000,
      R2004,
      R2007,
      R2010,

      Unknown
    };

  ////////////////////////////////////////////////////////////////
  // Members
  ////////////////////////////////////////////////////////////////
  private:
    Release release_;

    size_t version_;

  ////////////////////////////////////////////////////////////////
  // Constructors & Destructor
  ////////////////////////////////////////////////////////////////
  public:
    Version() :
    release_(Unknown),
    version_(0)
    {
    }

    Version(Release release, size_t maintenance = 0) :
    release_(release),
    version_(maintenance)
    {
    }

  ////////////////////////////////////////////////////////////////
  // Functions
  ////////////////////////////////////////////////////////////////
  public:
    bool isAtLeast(Release release, size_t maintenance = 0) const
    {
      if (release_ > release)
        return true;
      else if (release_ < release)
        return false;
      else
        return version_ >= maintenance;
    }

    bool isGreaterThan(Release release, size_t maintenance = 0) const
    {
      if (release_ > release)
        return true;
      else if (release_ < release)
        return false;
      else
        return version_ > maintenance;
    }

    void setMaintenance(size_t maintenance)
    {
      version_ = maintenance;
    }

    void setRelease(Release release)
    {
      release_ = release;
    }
};

////////////////////////////////////////////////////////////////

}
