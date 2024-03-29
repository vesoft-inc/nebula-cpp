/* Copyright (c) 2018 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License.
 */

#pragma once

#include <string>
#include <vector>

#include "common/datatypes/Geography.h"

namespace nebula {
namespace geo {

class WKTWriter {
 public:
  WKTWriter() {}

  ~WKTWriter() {}

  std::string write(const Geography& geog) const;

  void writeCoordinate(std::string& wkt, const Coordinate& coord) const;

  void writeCoordinateList(std::string& wkt, const std::vector<Coordinate>& coordList) const;

  void writeCoordinateListList(std::string& wkt,
                               const std::vector<std::vector<Coordinate>>& coordListList) const;

  void writeDouble(std::string& wkt, double v) const;
};

}  // namespace geo
}  // namespace nebula
