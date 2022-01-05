#include "hittable.hpp"

namespace core
{

void HitRecord::set_face_normal(Ray const &ray, Vec3 const &outward_normal)
{
  this->front_face = dot(ray.direction(), outward_normal) < 0;
  this->normal = front_face ? outward_normal : -outward_normal;
}

} // namespace core
