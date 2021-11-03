/* Copyright (c) 2020 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License.
 */

#pragma once

#include "common/datatypes/Value.h"

// Do not include <s2/s2polygon.h> here, it will indirectly includes a header file which defines a
// enum `BEGIN`(not enum class). While Geography.h is indirectly included by parser.yy, which has a
// macro named `BEGIN`. So they will be conflicted.

class S2Polygon;

namespace nebula {

// clang-format off
/*
static const std::unordered_map<GeoShape, S2Region> kShapeTypeToS2Region = {
    // S2PointRegion is a wrapper of S2Point, and it inherits from the S2Region class while S2Point doesn't.
    {GeoShape::POINT, S2PointRegion},
    {GeoShape::LINESTRING, S2Polyline},
    {GeoShape::POLYGON, S2Polygon},
};
*/
// clang-format on

// Do not construct a S2 object when constructing Geography. It's expensive.
// We just construct S2 when doing computation.
struct Geography {
  std::string wkb;  // TODO(jie) Is it better to store Geometry* or S2Region* here?

  Geography() = default;

  std::string toString() const { return wkb; }

  void clear() { wkb.clear(); }

  void __clear() { clear(); }

  bool operator==(const Geography& rhs) const { return wkb == rhs.wkb; }

  bool operator!=(const Geography& rhs) const { return !(wkb == rhs.wkb); }

  bool operator<(const Geography& rhs) const { return wkb < rhs.wkb; }

 private:
  explicit Geography(const std::string& bytes) {
    // TODO(jie): Must ensure the bytes is valid
    wkb = bytes;
  }
};

inline std::ostream& operator<<(std::ostream& os, const Geography& g) { return os << g.wkb; }

}  // namespace nebula

namespace std {

// Inject a customized hash function
template <>
struct hash<nebula::Geography> {
  std::size_t operator()(const nebula::Geography& h) const noexcept;
};

}  // namespace std
