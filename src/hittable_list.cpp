#include "hittable_list.hpp"

namespace core
{

auto HittableList::entries() const -> std::vector<std::shared_ptr<Hittable>>
{
  return this->m_hittables;
}

auto HittableList::entries() -> std::vector<std::shared_ptr<Hittable>> &
{
  return this->m_hittables;
}

void HittableList::clear()
{
  this->m_hittables.clear();
}

void HittableList::push_back(std::shared_ptr<Hittable> hittable)
{
  this->m_hittables.push_back(hittable);
}

} // namespace core
