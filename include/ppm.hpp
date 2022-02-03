#pragma once

#include <string>
#include <filesystem>
#include <vector>

#include "vec3.hpp"

namespace ppm
{

void write_file(std::filesystem::path const &path, char const *data, std::size_t const data_len);
auto from_pixels(std::vector<core::Vec3> const &pixels, std::size_t img_width, std::size_t img_height, std::size_t samples_per_pixel) -> std::string;

} // namespace ppm
