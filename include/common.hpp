#pragma once

#include <limits>
#include <random>

#include "xoshiro256ss.hpp"

namespace constants
{

constexpr double infinity = std::numeric_limits<double>::infinity();
constexpr double pi = 3.14159265358979323846;

} // namespace constants


namespace util
{

constexpr double degrees_to_radians(double degrees)
{
  return (degrees * constants::pi) / 180;
}


inline double random_double()
{
  // auto random_engine = std::mt19937{std::random_device{}()};
  auto random_engine = xoshiro256ss{std::random_device{}()};

  std::uniform_real_distribution<double> distribution(0.0, 1.0);
  return distribution(random_engine);
}

inline double random_double(double min, double max)
{
  // auto random_engine = std::mt19937{std::random_device{}()};
  auto random_engine = xoshiro256ss{std::random_device{}()};

  std::uniform_real_distribution<double> distribution(min, max);
  return distribution(random_engine);
}


inline auto xy_to_idx(std::size_t x, std::size_t y, std::size_t img_width) -> std::size_t
{
  return (img_width * y) + x;
};


} // namespace util
