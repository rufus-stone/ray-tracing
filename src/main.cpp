#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <chrono>

#include <spdlog/spdlog.h>

#include "common.hpp"
#include "hittable_list.hpp"
#include "ppm.hpp"
#include "vec3.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include "camera.hpp"
#include "renderer.hpp"

using namespace std::chrono_literals;

int main()
{
  // Start the clock
  auto const start = std::chrono::high_resolution_clock::now();

  // Image setup
  constexpr double ASPECT_RATIO = 16.0 / 9.0;
  constexpr std::size_t IMG_WIDTH = 1024;
  constexpr std::size_t IMG_HEIGHT = static_cast<std::size_t>(IMG_WIDTH / ASPECT_RATIO);
  constexpr std::size_t SAMPLES_PER_PIXEL = 20; // 100 is sloooww
  constexpr std::size_t MAX_DEPTH = 10;         // 50

  spdlog::info("Rendering {}x{} image @ {} samples/pixel with max depth of {}", IMG_WIDTH, IMG_HEIGHT, SAMPLES_PER_PIXEL, MAX_DEPTH);

  // World setup
  auto world = core::HittableList{};
  world.push_back(std::make_shared<core::Sphere>(core::Vec3{0, 0, -1}, 0.5));
  world.push_back(std::make_shared<core::Sphere>(core::Vec3{0, -100.5, -1}, 100));

  // Camera setup
  auto const camera = core::Camera{};

  // Ray trace pixels
  std::vector<core::Vec3> const pixels = core::render(world, camera, IMG_WIDTH, IMG_HEIGHT, SAMPLES_PER_PIXEL, MAX_DEPTH);

  // Generate PPM image string
  std::string const rendered = ppm::from_pixels(pixels, IMG_WIDTH, IMG_HEIGHT, SAMPLES_PER_PIXEL);

  // Write image to file
  ppm::write_file("rendered.ppm", rendered.data(), rendered.size());

  // Stop the clock
  auto const finish = std::chrono::high_resolution_clock::now();
  auto const nanoseconds_taken = (finish - start);
  auto const seconds_taken = std::chrono::duration<double, std::ratio<1>>(nanoseconds_taken).count();

  spdlog::info("Rendered in {:.0f} seconds ({:0.2f} minutes)", seconds_taken, seconds_taken / 60);

  return EXIT_SUCCESS;
}
