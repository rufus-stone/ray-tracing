#include <cstdlib>
#include <spdlog/spdlog.h>

#include "ppm.hpp"
#include "vec3.hpp"
#include "ray.hpp"

#include <iostream>

int main()
{
  // Image setup
  constexpr double ASPECT_RATIO = 16.0 / 9.0;
  constexpr int IMG_WIDTH = 1024;
  constexpr int IMG_HEIGHT = static_cast<int>(IMG_WIDTH / ASPECT_RATIO);

  spdlog::info("Image size: {}x{}", IMG_WIDTH, IMG_HEIGHT);

  // Camera setup
  constexpr double VIEWPORT_HEIGHT = 2.0;
  constexpr double VIEWPORT_WIDTH = ASPECT_RATIO * VIEWPORT_HEIGHT;
  constexpr double FOCAL_LENGTH = 1.0;

  spdlog::info("Viewport size: {}x{}", VIEWPORT_HEIGHT, VIEWPORT_WIDTH);
  spdlog::info("Focal length: {}", FOCAL_LENGTH);

  auto const camera_origin = core::Vec3{};
  auto const horizontal = core::Vec3{VIEWPORT_WIDTH, 0, 0};
  auto const vertical = core::Vec3(0, VIEWPORT_HEIGHT, 0);
  core::Vec3 const lower_left_corner = camera_origin - horizontal / 2 - vertical / 2 - core::Vec3(0, 0, FOCAL_LENGTH);

  spdlog::info("Camera origin: {}", camera_origin);
  spdlog::info("Lower left corner: {}", lower_left_corner);


  // Render
  auto ss = std::stringstream{};

  ss << "P3\n"
     << IMG_WIDTH << ' ' << IMG_HEIGHT << "\n255\n";

  for (int h = IMG_HEIGHT - 1; h >= 0; --h)
  {
    std::cerr << "\rScanlines remaining: " << h << ' ' << std::flush;

    for (int w = IMG_WIDTH - 1; w >= 0; w--)
    {
      double const u = static_cast<double>(w) / (IMG_WIDTH - 1);
      double const v = static_cast<double>(h) / (IMG_HEIGHT - 1);

      auto const ray = core::Ray{camera_origin, lower_left_corner + u * horizontal + v * vertical - camera_origin};
      auto const pixel_colour = core::ray_colour(ray);

      ss << core::colour_to_string(pixel_colour) << '\n';
    }
  }

  std::cerr << '\n';

  std::string const rendered = ss.str();

  ppm::write_file("rendered.ppm", rendered.data(), rendered.size());


  return EXIT_SUCCESS;
}