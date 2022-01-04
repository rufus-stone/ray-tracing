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
  Vec3 origin() const;
  Vec3 direction() const;
  Vec3 at(double t) const;

  // Operators
  auto operator<=>(Ray const &r) const = default; // Spaceship comparison
};

// Utility functions
template<typename OStream>
OStream &operator<<(OStream &os, Ray const &r)
{
  return os << "Ray { origin: " << r.origin() << ", direction: " << r.direction() << " }";
}

} // namespace core
