#pragma once

#include <vector>

#include "vec3.hpp"
#include "camera.hpp"
#include "hittable_list.hpp"

namespace core
{

/// Do the actual ray tracing
auto render(core::HittableList const &world, core::Camera const &camera, std::size_t img_width, std::size_t img_height, std::size_t samples_per_pixel, std::size_t max_depth) -> std::vector<core::Vec3>;

} // namespace core
