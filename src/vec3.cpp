#include "vec3.hpp"

#include <stdexcept> // std::out_of_range

namespace core
{

// Getters
double Vec3::x() const
{
  return this->m_x;
}

double Vec3::y() const
{
  return this->m_y;
}

double Vec3::z() const
{
  return this->m_z;
}

double Vec3::operator[](int i) const
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

double Vec3::length() const
{
  return std::sqrt(this->length_squared());
}

double Vec3::length_squared() const
{
  return std::pow(this->m_x, 2) + std::pow(this->m_y, 2) + std::pow(this->m_z, 2);
}

Vec3 Vec3::unit_vector() const
{
  return *this / this->length();
}

// Operators
Vec3 Vec3::operator-() const
{
  return Vec3{-this->x(), -this->y(), -this->z()};
}


Vec3 &Vec3::operator++() // Pre-increment
{
  this->m_x += 1;
  this->m_y += 1;
  this->m_z += 1;

  return *this;
}

Vec3 Vec3::operator++(int) // Post-increment
{
  Vec3 old = *this;
  this->operator++();
  return old;
}

Vec3 &Vec3::operator--() // Pre-decrement
{
  this->m_x -= 1;
  this->m_y -= 1;
  this->m_z -= 1;

  return *this;
}

Vec3 Vec3::operator--(int) // Post-decrement
{
  Vec3 old = *this;
  this->operator--();
  return old;
}

Vec3 &Vec3::operator+=(Vec3 const &v) // Add-equals
{
  this->m_x += v.x();
  this->m_y += v.y();
  this->m_z += v.z();

  return *this;
}

Vec3 &Vec3::operator-=(Vec3 const &v) // Subtract-equals
{
  this->m_x -= v.x();
  this->m_y -= v.y();
  this->m_z -= v.z();

  return *this;
}

Vec3 &Vec3::operator*=(Vec3 const &v) // Multiply-equals
{
  this->m_x *= v.x();
  this->m_y *= v.y();
  this->m_z *= v.z();

  return *this;
}

Vec3 &Vec3::operator/=(Vec3 const &v) // Divide-equals
{
  this->m_x /= v.x();
  this->m_y /= v.y();
  this->m_z /= v.z();

  return *this;
}

Vec3 &Vec3::operator+=(double const t) // Add-equals
{
  this->m_x += t;
  this->m_y += t;
  this->m_z += t;

  return *this;
}

Vec3 &Vec3::operator-=(double const t) // Subtract-equals
{
  this->m_x -= t;
  this->m_y -= t;
  this->m_z -= t;

  return *this;
}

Vec3 &Vec3::operator*=(double const t) // Multiply-equals
{
  this->m_x *= t;
  this->m_y *= t;
  this->m_z *= t;

  return *this;
}

Vec3 &Vec3::operator/=(double const t) // Divide-equals
{
  this->m_x /= t;
  this->m_y /= t;
  this->m_z /= t;

  return *this;
}


// Utility function
Vec3 operator+(Vec3 const &lhs, Vec3 const &rhs) // Add
{
  return Vec3{lhs.x() + rhs.x(), lhs.y() + rhs.y(), lhs.z() + rhs.z()};
}

Vec3 operator+(Vec3 const &lhs, double const rhs) // Add
{
  return Vec3{lhs.x() + rhs, lhs.y() + rhs, lhs.z() + rhs};
}

Vec3 operator+(double const lhs, Vec3 const &rhs) // Add
{
  return Vec3{lhs + rhs.x(), lhs + rhs.y(), lhs + rhs.z()};
}

Vec3 operator-(double const lhs, Vec3 const &rhs) // Subtract
{
  return Vec3{lhs - rhs.x(), lhs - rhs.y(), lhs - rhs.z()};
}

Vec3 operator-(Vec3 const &lhs, Vec3 const &rhs) // Subtract
{
  return Vec3{lhs.x() - rhs.x(), lhs.y() - rhs.y(), lhs.z() - rhs.z()};
}

Vec3 operator-(Vec3 const &lhs, double const rhs) // Subtract
{
  return Vec3{lhs.x() - rhs, lhs.y() - rhs, lhs.z() - rhs};
}

Vec3 operator*(double const lhs, Vec3 const &rhs) // Multiply
{
  return Vec3{lhs * rhs.x(), lhs * rhs.y(), lhs * rhs.z()};
}

Vec3 operator*(Vec3 const &lhs, Vec3 const &rhs) // Multiply
{
  return Vec3{lhs.x() * rhs.x(), lhs.y() * rhs.y(), lhs.z() * rhs.z()};
}

Vec3 operator*(Vec3 const &lhs, double const rhs) // Multiply
{
  return Vec3{lhs.x() * rhs, lhs.y() * rhs, lhs.z() * rhs};
}

Vec3 operator/(double const lhs, Vec3 const &rhs) // Divide
{
  return Vec3{lhs / rhs.x(), lhs / rhs.y(), lhs / rhs.z()};
}

Vec3 operator/(Vec3 const &lhs, Vec3 const &rhs) // Divide
{
  return Vec3{lhs.x() / rhs.x(), lhs.y() / rhs.y(), lhs.z() / rhs.z()};
}

Vec3 operator/(Vec3 const &lhs, double const rhs) // Divide
{
  return Vec3{lhs.x() / rhs, lhs.y() / rhs, lhs.z() / rhs};
}


double dot(Vec3 const &lhs, Vec3 const &rhs)
{
  return (lhs.x() * rhs.x()) + (lhs.y() * rhs.y()) + (lhs.z() * rhs.z());
}

Vec3 cross(Vec3 const &lhs, Vec3 const &rhs)
{
  return Vec3{(lhs.y() * rhs.z()) - (lhs.z() * rhs.y()),
    (lhs.z() * rhs.x()) - (lhs.x() * rhs.z()),
    (lhs.x() * rhs.y()) - (lhs.y() * rhs.x())};
}

} // namespace core
