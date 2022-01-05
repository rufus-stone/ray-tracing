#include "ray.hpp"

namespace core
{

// Getters
Vec3 Ray::origin() const
{
  return this->m_origin;
}

Vec3 Ray::direction() const
{
  return this->m_direction;
}

Vec3 Ray::at(double t) const
{
  return this->m_origin + (t * this->m_direction);
}

/// Check if a ray hits a sphere
double hit_sphere(Vec3 const &sphere_centre, double const sphere_radius, Ray const &ray)
{
  Vec3 const oc = ray.origin() - sphere_centre;
  double const a = ray.direction().length_squared();
  double const half_b = dot(oc, ray.direction());
  double const c = oc.length_squared() - (sphere_radius * sphere_radius);
  double const discriminant = (half_b * half_b) - (a * c);

  if (discriminant < 0.0)
  {
    return -1.0;
  } else
  {
    return (-half_b - std::sqrt(discriminant)) / a;
  }
}

/// Calculate the colour of the ray
Vec3 ray_colour(Ray const &ray, Hittable const &world)
{
  auto hit_record = HitRecord{};

  // Check if the ray hit anything in the world at any point
  if (world.hit(ray, 0, constants::infinity, hit_record))
  {
    return 0.5 * (hit_record.normal + Vec3{1, 1, 1});
  }

  Vec3 unit_direction = ray.direction().unit_vector();

  double const t = 0.5 * (unit_direction.y() + 1.0);

  Vec3 colour = (1.0 - t) * Vec3{1.0, 1.0, 1.0} + (t * Vec3{0.5, 0.7, 1.0});

  return colour;
}


} // namespace core