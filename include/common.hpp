#pragma once

#include <limits>

namespace constants
{

constexpr double infinity = std::numeric_limits<double>::infinity();
constexpr double pi = 3.14159265358979323846;

} // namespace constants


namespace util
{

constexpr double degrees_to_radians(double const degrees)
{
  return (degrees * constants::pi) / 180;
}

} // namespace util
