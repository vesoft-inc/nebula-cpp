/* Copyright (c) 2020 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License.
 */

#include "common/datatypes/Geography.h"

#include <folly/String.h>
#include <folly/hash/Hash.h>
#include <glog/logging.h>

#include <cstdint>

#include "common/geo/io/wkb/WKBWriter.h"
#include "common/geo/io/wkt/WKTWriter.h"

namespace nebula {

std::ostream& operator<<(std::ostream& os, const GeoShape& shape) {
  switch (shape) {
    case GeoShape::POINT: {
      os << "POINT";
      break;
    }
    case GeoShape::LINESTRING: {
      os << "LINESTRING";
      break;
    }
    case GeoShape::POLYGON: {
      os << "POLYGON";
      break;
    }
    case GeoShape::UNKNOWN:
    default: {
      os << "__UNKNOWN__";
      break;
    }
  }

  return os;
}

GeoShape Geography::shape() const {
  switch (geo_.index()) {
    case 0:
      return GeoShape::POINT;
    case 1:
      return GeoShape::LINESTRING;
    case 2:
      return GeoShape::POLYGON;
    default:  // May never reaches here, because the default constructor of the variant geo_ will
              // hold the value-initialized value of the first alternative(Point).
      return GeoShape::UNKNOWN;
  }
}

const Point& Geography::point() const {
  CHECK(std::holds_alternative<Point>(geo_));
  return std::get<Point>(geo_);
}

const LineString& Geography::lineString() const {
  CHECK(std::holds_alternative<LineString>(geo_));
  return std::get<LineString>(geo_);
}

const Polygon& Geography::polygon() const {
  CHECK(std::holds_alternative<Polygon>(geo_));
  return std::get<Polygon>(geo_);
}

Point& Geography::mutablePoint() {
  CHECK(std::holds_alternative<Point>(geo_));
  return std::get<Point>(geo_);
}

LineString& Geography::mutableLineString() {
  CHECK(std::holds_alternative<LineString>(geo_));
  return std::get<LineString>(geo_);
}

Polygon& Geography::mutablePolygon() {
  CHECK(std::holds_alternative<Polygon>(geo_));
  return std::get<Polygon>(geo_);
}

std::string Geography::asWKT() const { return geo::WKTWriter().write(*this); }

std::string Geography::asWKB() const { return geo::WKBWriter().write(*this); }

bool Geography::operator==(const Geography& rhs) const {
  auto lhsShape = shape();
  auto rhsShape = rhs.shape();
  if (lhsShape != rhsShape) {
    return false;
  }

  switch (lhsShape) {
    case GeoShape::POINT: {
      return point() == rhs.point();
    }
    case GeoShape::LINESTRING: {
      return lineString() == rhs.lineString();
    }
    case GeoShape::POLYGON: {
      return polygon() == rhs.polygon();
    }
    case GeoShape::UNKNOWN:
    default: {
      LOG(ERROR) << "Geography shapes other than Point/LineString/Polygon are not currently "
                    "supported";
      return false;
    }
  }
}

bool Geography::operator<(const Geography& rhs) const {
  auto lhsShape = shape();
  auto rhsShape = rhs.shape();
  if (lhsShape != rhsShape) {
    return lhsShape < rhsShape;
  }

  switch (lhsShape) {
    case GeoShape::POINT: {
      return point() < rhs.point();
    }
    case GeoShape::LINESTRING: {
      return lineString() < rhs.lineString();
    }
    case GeoShape::POLYGON: {
      return polygon() < rhs.polygon();
    }
    case GeoShape::UNKNOWN:
    default: {
      LOG(ERROR) << "Geography shapes other than Point/LineString/Polygon are not currently "
                    "supported";
      return false;
    }
  }
  return false;
}

}  // namespace nebula

namespace std {

// Inject a customized hash function
std::size_t hash<nebula::Geography>::operator()(const nebula::Geography& v) const noexcept {
  std::string wkb = v.asWKB();
  return hash<std::string>{}(wkb);
}

}  // namespace std
