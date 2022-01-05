#pragma once

#include "ray.hpp"
#include "vec3.hpp"

namespace core
{

class Camera
{
private:
  Vec3 m_origin;
  Vec3 m_lower_left_corner;
  Vec3 m_horizontal;
  Vec3 m_vertical;

public:
  constexpr Camera()
  {
    double aspect_ratio = 16.0 / 9.0;
    double viewport_height = 2.0;
    double viewport_width = aspect_ratio * viewport_height;
    double focal_length = 1.0;

    this->m_origin = core::Vec3{0, 0, 0};
    this->m_horizontal = core::Vec3{viewport_width, 0, 0};
    this->m_vertical = core::Vec3(0, viewport_height, 0);
    this->m_lower_left_corner = this->m_origin - (this->m_horizontal / 2) - (this->m_vertical / 2) - core::Vec3(0, 0, focal_length);
  }


  constexpr Camera(double aspect_ratio, double viewport_height, double focal_length, Vec3 const &origin)
  {
    double viewport_width = aspect_ratio * viewport_height;

    this->m_origin = origin;
    this->m_horizontal = core::Vec3{viewport_width, 0, 0};
    this->m_vertical = core::Vec3(0, viewport_height, 0);
    this->m_lower_left_corner = this->m_origin - (this->m_horizontal / 2) - (this->m_vertical / 2) - core::Vec3(0, 0, focal_length);
  }

  ~Camera() noexcept = default;

  constexpr Camera(Camera const &other) = default;     // copy constructor
  constexpr Camera(Camera &&other) noexcept = default; // move constructor

  constexpr Camera &operator=(Camera const &other) = default;     // copy assignment
  constexpr Camera &operator=(Camera &&other) noexcept = default; // move assignment

  Ray get_ray(double const u, double const v) const;

  constexpr bool operator==(Camera const &c) const = default; // Equality comparison
};

} // namespace core
