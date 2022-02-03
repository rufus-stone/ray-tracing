#include "renderer.hpp"

#include <iostream>

#include "common.hpp"

namespace core
{

auto render(core::HittableList const &world, core::Camera const &camera, std::size_t img_width, std::size_t img_height, std::size_t samples_per_pixel, std::size_t max_depth) -> std::vector<core::Vec3>
{
  auto output = std::vector<core::Vec3>(img_width * img_height, core::Vec3{});

  // This is ripe for parallelisation
  for (int h = img_height - 1; h >= 0; --h)
  {
    std::cerr << "\rScanlines remaining: " << h << ' ' << std::flush;

    for (int w = img_width - 1; w >= 0; w--)
    {
      auto pixel_colour = core::Vec3{0, 0, 0};

      for (std::size_t s = 0; s < samples_per_pixel; ++s)
      {
        double u = (w + util::random_double()) / (img_width - 1);
        double v = (h + util::random_double()) / (img_height - 1);

        auto const ray = camera.get_ray(u, v);

        pixel_colour += core::ray_colour(ray, world, max_depth);
      }

      output[util::xy_to_idx((img_width - 1) - w, (img_height - 1) - h, img_width)] = pixel_colour;
    }
  }

  std::cerr << '\n';

  return output;
}

} // namespace core
