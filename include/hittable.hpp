#pragma once

#include <spdlog/fmt/ostr.h> // for spdlog pretty printing, etc.

#include "vec3.hpp"
#include "ray.hpp"

namespace core
{

class Ray;

struct HitRecord
{
  Vec3 point;
  Vec3 normal;
  double t;
  bool front_face;

  void set_face_normal(Ray const &ray, Vec3 const &outward_normal);

  auto operator<=>(HitRecord const &h) const = default; // Spaceship comparison
};


// Utility functions
template<typename OStream>
OStream &operator<<(OStream &os, HitRecord const &h)
{
  return os << "HitRecord { point: " << h.point << ", normal: " << h.normal << ", t: " << h.t << ", front_face: " << h.front_face << " }";
}


class Hittable
{
public:
  virtual bool hit(Ray const &ray, double const t_min, double const t_max, HitRecord &hit_record) const = 0;
};

} // namespace core
