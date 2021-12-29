#pragma once

#include "spdlog/fmt/ostr.h" // must be included

namespace core
{

class Vec3
{
private:
  double m_x = 0.0;
  double m_y = 0.0;
  double m_z = 0.0;

public:
  Vec3() = default;
  ~Vec3() noexcept = default;

  Vec3(double x, double y, double z);

  Vec3(Vec3 const &other) = default;     // copy constructor
  Vec3(Vec3 &&other) noexcept = default; // move constructor

  Vec3 &operator=(Vec3 const &other) = default;     // copy assignment
  Vec3 &operator=(Vec3 &&other) noexcept = default; // move assignment

  double x() const;
  double y() const;
  double z() const;

  template<typename OStream>
  friend OStream &operator<<(OStream &os, Vec3 const &v)
  {
    return os << "Vec3 { x: " << v.x() << ", y: " << v.y() << ", z: " << v.z() << " }";
  }
};

} // namespace core
