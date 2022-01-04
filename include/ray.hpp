#pragma once

#include "vec3.hpp"

namespace core
{

class Ray
{
private:
  Vec3 m_origin;
  Vec3 m_direction;

public:
  Ray() = default;
  ~Ray() noexcept = default;

  constexpr Ray(Vec3 const &origin, Vec3 const &direction) : m_origin(origin), m_direction(direction) {}

  Ray(Ray const &other) = default;     // copy constructor
  Ray(Ray &&other) noexcept = default; // move constructor

  Ray &operator=(Ray const &other) = default;     // copy assignment
  Ray &operator=(Ray &&other) noexcept = default; // move assignment

  // Getters
  constexpr Vec3 origin() const
  {
    return this->m_origin;
  }

  constexpr Vec3 direction() const
  {
    return this->m_direction;
  }

  constexpr Vec3 at(double t) const
  {
    return this->m_origin + (t * this->m_direction);
  }

  // Operators
  // auto operator<=>(Ray const &r) const = default; // Spaceship comparison
  bool operator==(Ray const &r) const = default; // Equality comparison
};

// Utility functions
template<typename OStream>
OStream &operator<<(OStream &os, Ray const &r)
{
  return os << "Ray { origin: " << r.origin() << ", direction: " << r.direction() << " }";
}

/// Check if a ray hits a sphere
constexpr bool hit_sphere(Vec3 const &sphere_centre, double const sphere_radius, Ray const &ray)
{
  Vec3 const oc = ray.origin() - sphere_centre;
  double const a = dot(ray.direction(), ray.direction());
  double const b = 2.0 * dot(oc, ray.direction());
  double const c = dot(oc, oc) - (sphere_radius * sphere_radius);
  double const discriminant = b * b - 4 * a * c;
  return (discriminant > 0);
}


/// Calculate the colour of the ray
constexpr Vec3 ray_colour(Ray const &ray)
{
  // Check if the ray hit the sphere
  auto const sphere_origin = Vec3{0, 0, -1};
  double const sphere_radius = 0.5;
  if (hit_sphere(sphere_origin, sphere_radius, ray))
  {
    auto colour = Vec3{1, 0, 0};
    return colour;
  }

  Vec3 unit_direction = ray.direction().unit_vector();

  double const t = 0.5 * (unit_direction.y() + 1.0);

  Vec3 colour = (1.0 - t) * Vec3{1.0, 1.0, 1.0} + (t * Vec3{0.5, 0.7, 1.0});

  return colour;
}

} // namespace core
