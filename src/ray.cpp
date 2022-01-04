#include "ray.hpp"

namespace core
{

/// Get the origin of the ray
Vec3 Ray::origin() const
{
  return this->m_origin;
}

/// Get the direction of the ray
Vec3 Ray::direction() const
{
  return this->m_direction;
}

/// Get the point a position t along the ray
Vec3 Ray::at(double t) const
{
  return this->m_origin + (t * this->m_direction);
}

} // namespace core