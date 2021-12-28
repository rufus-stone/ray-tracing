#include <cstdlib>
#include <spdlog/spdlog.h>

#include "ppm.hpp"
#include "vec3.hpp"

int main()
{
  spdlog::info("Oh snap!");

  std::string const example = ppm::example();

  ppm::write_file("test.ppm", example.data(), example.size());

  return EXIT_SUCCESS;
}