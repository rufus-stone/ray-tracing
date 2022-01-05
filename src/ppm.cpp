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

} // namespace ppm
