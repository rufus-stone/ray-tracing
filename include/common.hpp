#pragma once

#include <limits>
#include <random>
#include <type_traits>

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


inline double random_double()
{
  auto random_engine = std::mt19937{std::random_device{}()};

  std::uniform_real_distribution<double> distribution(0.0, 1.0);
  return distribution(random_engine);
}

inline double random_double(double const min, double const max)
{
  auto random_engine = std::mt19937{std::random_device{}()};

  std::uniform_real_distribution<double> distribution(min, max);
  return distribution(random_engine);
}

} // namespace util
