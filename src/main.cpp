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

using namespace std::chrono_literals;

int main()
{
  auto const start = std::chrono::high_resolution_clock::now();

  // Image setup
  constexpr double ASPECT_RATIO = 16.0 / 9.0;
  constexpr int IMG_WIDTH = 1024;
  constexpr int IMG_HEIGHT = static_cast<int>(IMG_WIDTH / ASPECT_RATIO);
  constexpr std::size_t SAMPLES_PER_PIXEL = 20; // 100 is sloooww
  constexpr std::size_t MAX_DEPTH = 10;         // 50

  spdlog::info("Image size: {}x{}", IMG_WIDTH, IMG_HEIGHT);

  // World setup
  auto world = core::HittableList{};
  world.push_back(std::make_shared<core::Sphere>(core::Vec3{0, 0, -1}, 0.5));
  world.push_back(std::make_shared<core::Sphere>(core::Vec3{0, -100.5, -1}, 100));

  // Camera setup
  auto camera = core::Camera{};

  // Render
  auto ss = std::stringstream{};

  ss << "P3\n"
     << IMG_WIDTH << ' ' << IMG_HEIGHT << "\n255\n";

  for (int h = IMG_HEIGHT - 1; h >= 0; --h)
  {
    std::cerr << "\rScanlines remaining: " << h << ' ' << std::flush;

    for (int w = IMG_WIDTH - 1; w >= 0; w--)
    {
      auto pixel_colour = core::Vec3{0, 0, 0};

      for (std::size_t s = 0; s < SAMPLES_PER_PIXEL; ++s)
      {
        double u = (w + util::random_double()) / (IMG_WIDTH - 1);
        double v = (h + util::random_double()) / (IMG_HEIGHT - 1);

        auto const ray = camera.get_ray(u, v);

        pixel_colour += core::ray_colour(ray, world, MAX_DEPTH);
      }

      ss << core::colour_to_string(pixel_colour, SAMPLES_PER_PIXEL) << '\n';
    }
  }

  std::cerr << '\n';

  std::string const rendered = ss.str();

  ppm::write_file("rendered.ppm", rendered.data(), rendered.size());


  auto const finish = std::chrono::high_resolution_clock::now();
  auto const nanoseconds_taken = (finish - start);
  auto const seconds_taken = std::chrono::duration<double, std::ratio<1>>(nanoseconds_taken).count();

  spdlog::info("Rendered in {:.0f} seconds ({:0.2f} minutes)", seconds_taken, seconds_taken / 60);

  return EXIT_SUCCESS;
}