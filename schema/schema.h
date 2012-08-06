#pragma once

#include "../includes.h"

namespace libredwgpp {

class Face3d;
class Vertex3d;

class ISchema
{
  ////////////////////////////////////////////////////////////////
  // Definitions
  ////////////////////////////////////////////////////////////////
  public:

  ////////////////////////////////////////////////////////////////
  // Members
  ////////////////////////////////////////////////////////////////
  private:

  ////////////////////////////////////////////////////////////////
  // Constructors & Destructor
  ////////////////////////////////////////////////////////////////
  public:
    virtual ~ISchema() {}

  ////////////////////////////////////////////////////////////////
  // Operators
  ////////////////////////////////////////////////////////////////
  private:

  ////////////////////////////////////////////////////////////////
  // Functions
  ////////////////////////////////////////////////////////////////
  public:
    /// Add a triangle to display
    virtual void addFace3d(const Face3d& face) = 0;

    /// Add a line to display
    virtual void addLine(size_t id, const Vertex3d& start, const Vertex3d& end,
                         double thickness, const Vertex3d& extrusion) = 0;

    /// Start a block
    virtual void blockStart(size_t id, const UnicodeString& strName) = 0;

    /// End a block
    virtual void blockEnd() = 0;

    /// Insert an element, applying some transformations
    /// The scaling is applied first (?)
    /// The rotation is applied second (?)
    /// The translation is applied last
    virtual void insert(size_t elt_id, const Vertex3d& rotAxis, double rotRad,
                        const Vertex3d& scaling, const Vertex3d& translation) = 0;

//    /// Apply a transformation to all subsequent faces
//    /// The scaling is applied first (?)
//    /// The rotation is applied second (?)
//    /// The translation is applied last
//    virtual void setTransformationMatrix(const Vertex3d& rotAxis, double rotRad,
//                                         const Vertex3d& scaling, const Vertex3d& translation) = 0;

//    virtual const std::vector<Face3d>& getFaces3d() const = 0;
};

////////////////////////////////////////////////////////////////

}
