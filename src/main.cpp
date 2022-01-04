#include <cstdlib>
#include <spdlog/spdlog.h>

#include "ppm.hpp"
#include "vec3.hpp"

#include <iostream>

int main()
{
  spdlog::info("Oh snap!");

  std::string const example = ppm::example_two();

  ppm::write_file("test.ppm", example.data(), example.size());


  auto v = core::Vec3{1.0, 2.0, 3.0};

  spdlog::info("{}", v);


  return EXIT_SUCCESS;
}