#include "camera.hpp"

namespace core
{

Ray Camera::get_ray(double const u, double const v) const
{
  return Ray{this->m_origin, this->m_lower_left_corner + (u * this->m_horizontal) + (v * this->m_vertical) - this->m_origin};
}

} // namespace core
