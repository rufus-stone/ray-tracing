#include "vec3.hpp"

#include <stdexcept> // std::out_of_range

namespace core
{


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

} // namespace core
