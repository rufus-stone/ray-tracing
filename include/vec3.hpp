#pragma once

#include <cmath>
#include <compare>

#include "spdlog/fmt/ostr.h" // must be included

namespace core
{

class Vec3
{
private:
  double m_x = 0.0;
  double m_y = 0.0;
  double m_z = 0.0;

public:
  Vec3() = default;
  ~Vec3() noexcept = default;

  constexpr Vec3(double x, double y, double z) : m_x(x), m_y(y), m_z(z) {}

  Vec3(Vec3 const &other) = default;     // copy constructor
  Vec3(Vec3 &&other) noexcept = default; // move constructor

  Vec3 &operator=(Vec3 const &other) = default;     // copy assignment
  Vec3 &operator=(Vec3 &&other) noexcept = default; // move assignment

  // Getters
  double x() const;
  double y() const;
  double z() const;
  double operator[](int i) const;

  // Operators
  auto operator<=>(Vec3 const &) const = default; // Spaceship comparison

  Vec3 operator-() const; // Invert
  Vec3 &operator++();     // Pre-increment
  Vec3 operator++(int);   // Post-increment
  Vec3 &operator--();     // Pre-decrement
  Vec3 operator--(int);   // Post-decrement

  Vec3 &operator+=(Vec3 const &v); // Add-equals
  Vec3 &operator-=(Vec3 const &v); // Subtract-equals
  Vec3 &operator*=(Vec3 const &v); // Multiply-equals
  Vec3 &operator/=(Vec3 const &v); // Divide-equals

  Vec3 &operator+=(double const t); // Add-equals
  Vec3 &operator-=(double const t); // Subtract-equals
  Vec3 &operator*=(double const t); // Multiply-equals
  Vec3 &operator/=(double const t); // Divide-equals

  double length() const
  {
    return std::sqrt(this->length_squared());
  }

  double length_squared() const
  {
    return std::pow(this->m_x, 2) + std::pow(this->m_y, 2) + std::pow(this->m_z, 2);
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
Vec3 operator-(Vec3 const &lhs, Vec3 const &rhs);  // Subtract
Vec3 operator-(Vec3 const &lhs, double const rhs); // Subtract
Vec3 operator-(double const lhs, Vec3 const &rhs); // Subtract
Vec3 operator*(Vec3 const &lhs, Vec3 const &rhs);  // Multiply
Vec3 operator*(Vec3 const &lhs, double const rhs); // Multiply
Vec3 operator*(double const lhs, Vec3 const &rhs); // Multiply
Vec3 operator/(Vec3 const &lhs, Vec3 const &rhs);  // Divide
Vec3 operator/(Vec3 const &lhs, double const rhs); // Divide
Vec3 operator/(double const lhs, Vec3 const &rhs); // Divide


} // namespace core
