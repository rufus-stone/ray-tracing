#include "vec3.hpp"

#include <spdlog/spdlog.h>

namespace core
{

Vec3::Vec3(double x, double y, double z) : m_x(x), m_y(y), m_z(z) {}

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

} // namespace core
