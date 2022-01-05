#pragma once

#include <memory>
#include <vector>

#include "hittable.hpp"


namespace core
{

class HittableList : public Hittable
{
private:
  std::vector<std::shared_ptr<Hittable>> m_hittables;

public:
  HittableList() = default;
  ~HittableList() noexcept = default;

  HittableList(std::shared_ptr<Hittable> hittable)
  {
    this->m_hittables.push_back(hittable);
  }

  HittableList(HittableList const &other) = default;     // copy constructor
  HittableList(HittableList &&other) noexcept = default; // move constructor

  HittableList &operator=(HittableList const &other) = default;     // copy assignment
  HittableList &operator=(HittableList &&other) noexcept = default; // move assignment

  auto entries() const -> std::vector<std::shared_ptr<Hittable>>;
  auto entries() -> std::vector<std::shared_ptr<Hittable>> &;

  void clear();
  void push_back(std::shared_ptr<Hittable> hittable);

  virtual bool hit(Ray const &ray, double const t_min, double const t_max, HitRecord &hit_record) const override
  {
    auto hit_record_temp = HitRecord{};
    bool hit_anything = false;

    double closest_so_far = t_max;

    for (auto const &hittable : this->m_hittables)
    {
      if (hittable->hit(ray, t_min, closest_so_far, hit_record_temp))
      {
        hit_anything = true;
        closest_so_far = hit_record_temp.t;
        hit_record = hit_record_temp;
      }
    }

    return hit_anything;
  }
};

} // namespace core
