#include "ppm.hpp"

#include <sstream>
#include <iostream>
#include <fstream>

#include <spdlog/spdlog.h>

namespace ppm
{

auto example() -> std::string
{
  static constexpr int IMG_WIDTH = 1024;
  static constexpr int IMG_HEIGHT = 1024;

  auto ss = std::stringstream{};

  ss << "P3\n"
     << IMG_WIDTH << ' ' << IMG_HEIGHT << "\n255\n";

  for (int h = IMG_HEIGHT - 1; h >= 0; h--)
  {
    std::cerr << "\rScanlines remaining: " << h << ' ' << std::flush;

    for (int w = IMG_WIDTH - 1; w >= 0; w--)
    {
      double const r = static_cast<double>(w) / (IMG_WIDTH - 1);
      double const g = static_cast<double>(h) / (IMG_HEIGHT - 1);
      double const b = 0.25;

      int const ir = static_cast<int>(r * 256.0);
      int const ig = static_cast<int>(g * 256.0);
      int const ib = static_cast<int>(b * 256.0);

      ss << ir << ' ' << ig << ' ' << ib << '\n';
    }
  }

  std::cerr << '\n';

  return ss.str();
}


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

} // namespace ppm
