#pragma once

#include "hittable.hpp"
#include "vec3.hpp"
#include "common.hpp"

namespace core
{

class Hittable;

class Ray
{
private:
  Vec3 m_origin;
  Vec3 m_direction;

public:
  constexpr Ray() = default;
  ~Ray() noexcept = default;

  constexpr Ray(Vec3 const &origin, Vec3 const &direction) : m_origin(origin), m_direction(direction) {}

  constexpr Ray(Ray const &other) = default;     // copy constructor
  constexpr Ray(Ray &&other) noexcept = default; // move constructor

  constexpr Ray &operator=(Ray const &other) = default;     // copy assignment
  constexpr Ray &operator=(Ray &&other) noexcept = default; // move assignment

  // Getters
  Vec3 origin() const;
  Vec3 direction() const;
  Vec3 at(double t) const;

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
double hit_sphere(Vec3 const &sphere_centre, double const sphere_radius, Ray const &ray);

/// Calculate the colour of the ray
Vec3 ray_colour(Ray const &ray, Hittable const &world);


} // namespace core
