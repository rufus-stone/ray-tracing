#include "ppm.hpp"

#include <sstream>
#include <iostream>
#include <fstream>

#include <spdlog/spdlog.h>

#include "vec3.hpp"

namespace ppm
{

void write_file(std::filesystem::path const &path, char const *data, std::size_t const data_len)
{
  spdlog::info("Writing {} bytes to file: {}", data_len, path.c_str());

  auto ofs = std::ofstream{path, std::ios::out | std::ios::binary};

  if (ofs.is_open())
  {
    ofs.write(data, data_len);
  }

  ofs.close();

  spdlog::info("Done");
}


auto from_pixels(std::vector<core::Vec3> const &pixels, std::size_t img_width, std::size_t img_height, std::size_t samples_per_pixel) -> std::string
{
  auto ss = std::stringstream{};

  ss << "P3\n"
     << img_width << ' ' << img_height << "\n255\n";

  for (core::Vec3 const &pixel : pixels)
  {
    ss << core::colour_to_string(pixel, samples_per_pixel) << '\n';
  }

  return ss.str();
}

} // namespace ppm
