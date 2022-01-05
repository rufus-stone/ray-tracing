#pragma once

#include <cmath>

#include "hittable.hpp"
#include "vec3.hpp"

namespace core
{

class Sphere : public Hittable
{
private:
  Vec3 m_centre_point;
  double m_radius = 0.0;

public:
  constexpr Sphere() = default;
  ~Sphere() noexcept = default;

  constexpr Sphere(Vec3 centre_point, double radius) : m_centre_point(centre_point), m_radius(radius) {}

  constexpr Sphere(Sphere const &other) = default;     // copy constructor
  constexpr Sphere(Sphere &&other) noexcept = default; // move constructor

  constexpr Sphere &operator=(Sphere const &other) = default;     // copy assignment
  constexpr Sphere &operator=(Sphere &&other) noexcept = default; // move assignment


  // Getters
  Vec3 const &centre() const
  {
    return this->m_centre_point;
  }

  double radius() const
  {
    return this->m_radius;
  }


  virtual bool hit(Ray const &ray, double const t_min, double const t_max, HitRecord &hit_record) const override
  {
    Vec3 const oc = ray.origin() - this->m_centre_point;
    double const a = ray.direction().length_squared();
    double const half_b = dot(oc, ray.direction());
    double const c = oc.length_squared() - (this->m_radius * this->m_radius);
    double const discriminant = (half_b * half_b) - (a * c);

    if (discriminant < 0.0)
    {
      return false;
    }

    double const discriminant_sqrt = std::sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range
    double root = (-half_b - discriminant_sqrt) / a;

    if (root < t_min || root > t_max)
    {
      root = (-half_b + discriminant_sqrt) / a;

      if (root < t_min || root > t_max)
      {
        return false;
      }
    }

    hit_record.t = root;
    hit_record.point = ray.at(root);

    // Determine which surface side the ray hit
    Vec3 const outward_normal = (hit_record.point - this->m_centre_point) / this->m_radius;
    hit_record.set_face_normal(ray, outward_normal);

    return true;
  }
};

} // namespace core
