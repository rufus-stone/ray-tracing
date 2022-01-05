#pragma once

#include <cmath>
#include <compare>
#include <algorithm> // std::clamp

#include <spdlog/fmt/ostr.h> // for spdlog pretty printing, etc.

#include "common.hpp"

namespace core
{

class Vec3
{
private:
  double m_x = 0.0;
  double m_y = 0.0;
  double m_z = 0.0;

public:
  constexpr Vec3() = default;
  ~Vec3() noexcept = default;

  constexpr Vec3(double x, double y, double z) : m_x(x), m_y(y), m_z(z) {}

  constexpr Vec3(Vec3 const &other) = default;     // copy constructor
  constexpr Vec3(Vec3 &&other) noexcept = default; // move constructor

  constexpr Vec3 &operator=(Vec3 const &other) = default;     // copy assignment
  constexpr Vec3 &operator=(Vec3 &&other) noexcept = default; // move assignment

  // Getters
  double x() const;
  double y() const;
  double z() const;
  double operator[](int i) const;

  double length() const;
  double length_squared() const;
  Vec3 unit_vector() const;

  // Operators
  auto operator<=>(Vec3 const &v) const = default; // Spaceship comparison

  Vec3 operator-() const;

  Vec3 &operator++();   // Pre-increment
  Vec3 operator++(int); // Post-increment
  Vec3 &operator--();   // Pre-decrement
  Vec3 operator--(int); // Post-decrement

  Vec3 &operator+=(Vec3 const &v); // Add-equals
  Vec3 &operator-=(Vec3 const &v); // Subtract-equals
  Vec3 &operator*=(Vec3 const &v); // Multiply-equals
  Vec3 &operator/=(Vec3 const &v); // Divide-equals

  Vec3 &operator+=(double const t); // Add-equals
  Vec3 &operator-=(double const t); // Subtract-equals
  Vec3 &operator*=(double const t); // Multiply-equals
  Vec3 &operator/=(double const t); // Divide-equals


  inline static Vec3 random()
  {
    return Vec3{util::random_double(), util::random_double(), util::random_double()};
  }

  inline static Vec3 random(double const min, double const max)
  {
    return Vec3{util::random_double(min, max), util::random_double(min, max), util::random_double(min, max)};
  }

  inline static Vec3 random_in_unit_sphere()
  {
    while (true)
    {
      auto const p = Vec3::random(-1, 1);

      if (p.length_squared() >= 1)
      {
        continue;
      } else
      {
        return p;
      }
    }
  }
};


// Utility functions
template<typename OStream>
OStream &operator<<(OStream &os, Vec3 const &v)
{
  return os << "Vec3 { x: " << v.x() << ", y: " << v.y() << ", z: " << v.z() << " }";
}

Vec3 operator+(Vec3 const &lhs, Vec3 const &rhs);  // Add
Vec3 operator+(Vec3 const &lhs, double const rhs); // Add
Vec3 operator+(double const lhs, Vec3 const &rhs); // Add

Vec3 operator-(double const lhs, Vec3 const &rhs); // Subtract
Vec3 operator-(Vec3 const &lhs, Vec3 const &rhs);  // Subtract
Vec3 operator-(Vec3 const &lhs, double const rhs); // Subtract

Vec3 operator*(double const lhs, Vec3 const &rhs); // Multiply
Vec3 operator*(Vec3 const &lhs, Vec3 const &rhs);  // Multiply
Vec3 operator*(Vec3 const &lhs, double const rhs); // Multiply

Vec3 operator/(double const lhs, Vec3 const &rhs); // Divide
Vec3 operator/(Vec3 const &lhs, Vec3 const &rhs);  // Divide
Vec3 operator/(Vec3 const &lhs, double const rhs); // Divide


double dot(Vec3 const &lhs, Vec3 const &rhs);
Vec3 cross(Vec3 const &lhs, Vec3 const &rhs);


inline std::string colour_to_string(Vec3 const &v, std::size_t const samples_per_pixel)
{
  // Divide the colour by the number of samples then gamma-correct for gamma=2.0
  // by raising the colour to the power of 1/gamma (so to the power of 1/2, which is just a square root)
  double const scale = 1.0 / samples_per_pixel;

  double const r = std::sqrt(v.x() * scale);
  double const g = std::sqrt(v.y() * scale);
  double const b = std::sqrt(v.z() * scale);

  int const red = static_cast<int>(std::clamp(r, 0.0, 0.999) * 256);
  int const green = static_cast<int>(std::clamp(g, 0.0, 0.999) * 256);
  int const blue = static_cast<int>(std::clamp(b, 0.0, 0.999) * 256);

  std::string output = std::to_string(red) + ' ' + std::to_string(green) + ' ' + std::to_string(blue);

  return output;
}

} // namespace core
