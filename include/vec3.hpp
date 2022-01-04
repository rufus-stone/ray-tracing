#pragma once

#include <cmath>
#include <compare>

#include <spdlog/fmt/ostr.h> // must be included

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
  constexpr double x() const
  {
    return this->m_x;
  }

  constexpr double y() const
  {
    return this->m_y;
  }

  constexpr double z() const
  {
    return this->m_z;
  }

  constexpr double operator[](int i) const
  {
    switch (i)
    {
      case 0:
        return this->m_x;
      case 1:
        return this->m_y;
      case 2:
        return this->m_z;
      default:
        throw std::out_of_range("Vec3::operator[] : index is out of range");
    }
  }

  // Operators
  auto operator<=>(Vec3 const &v) const = default; // Spaceship comparison

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

  double length() const;
  double length_squared() const;
  Vec3 unit_vector() const;
};


// Utility functions
template<typename OStream>
OStream &operator<<(OStream &os, Vec3 const &v)
{
  return os << "Vec3 { x: " << v.x() << ", y: " << v.y() << ", z: " << v.z() << " }";
}


constexpr Vec3 operator+(Vec3 const &lhs, Vec3 const &rhs) // Add
{
  return Vec3{lhs.x() + rhs.x(), lhs.y() + rhs.y(), lhs.z() + rhs.z()};
}

constexpr Vec3 operator+(Vec3 const &lhs, double const rhs) // Add
{
  return Vec3{lhs.x() + rhs, lhs.y() + rhs, lhs.z() + rhs};
}

constexpr Vec3 operator+(double const lhs, Vec3 const &rhs) // Add
{
  return Vec3{lhs + rhs.x(), lhs + rhs.y(), lhs + rhs.z()};
}


constexpr Vec3 operator-(Vec3 const &lhs, Vec3 const &rhs) // Subtract
{
  return Vec3{lhs.x() - rhs.x(), lhs.y() - rhs.y(), lhs.z() - rhs.z()};
}

constexpr Vec3 operator-(Vec3 const &lhs, double const rhs) // Subtract
{
  return Vec3{lhs.x() - rhs, lhs.y() - rhs, lhs.z() - rhs};
}

constexpr Vec3 operator-(double const lhs, Vec3 const &rhs) // Subtract
{
  return Vec3{lhs - rhs.x(), lhs - rhs.y(), lhs - rhs.z()};
}


constexpr Vec3 operator*(Vec3 const &lhs, Vec3 const &rhs) // Multiply
{
  return Vec3{lhs.x() * rhs.x(), lhs.y() * rhs.y(), lhs.z() * rhs.z()};
}

constexpr Vec3 operator*(Vec3 const &lhs, double const rhs) // Multiply
{
  return Vec3{lhs.x() * rhs, lhs.y() * rhs, lhs.z() * rhs};
}

constexpr Vec3 operator*(double const lhs, Vec3 const &rhs) // Multiply
{
  return Vec3{lhs * rhs.x(), lhs * rhs.y(), lhs * rhs.z()};
}


constexpr Vec3 operator/(Vec3 const &lhs, Vec3 const &rhs) // Divide
{
  return Vec3{lhs.x() / rhs.x(), lhs.y() / rhs.y(), lhs.z() / rhs.z()};
}

constexpr Vec3 operator/(Vec3 const &lhs, double const rhs) // Divide
{
  return Vec3{lhs.x() / rhs, lhs.y() / rhs, lhs.z() / rhs};
}

constexpr Vec3 operator/(double const lhs, Vec3 const &rhs) // Divide
{
  return Vec3{lhs / rhs.x(), lhs / rhs.y(), lhs / rhs.z()};
}


constexpr double dot(Vec3 const &lhs, Vec3 const &rhs)
{
  return (lhs.x() * rhs.x()) + (lhs.y() * rhs.y()) + (lhs.z() * rhs.z());
}

constexpr Vec3 cross(Vec3 const &lhs, Vec3 const &rhs)
{
  return Vec3{(lhs.y() * rhs.z()) - (lhs.z() * rhs.y()),
    (lhs.z() * rhs.x()) - (lhs.x() * rhs.z()),
    (lhs.x() * rhs.y()) - (lhs.y() * rhs.x())};
}


inline std::string colour_to_string(Vec3 const &v)
{
  std::string output = std::to_string(static_cast<int>(v.x() * 256)) + ' ' + std::to_string(static_cast<int>(v.y() * 256)) + ' ' + std::to_string(static_cast<int>(v.z() * 256));

  return output;
}

} // namespace core
