#include <catch2/catch_all.hpp>

#include "vec3.hpp"
#include "ray.hpp"
#include "sphere.hpp"

// +------------+
// | Vec3 tests |
// +------------+

TEST_CASE("Vec3", "[vec3][core]")
{
  auto v0 = core::Vec3{}; // 0.0, 0.0, 0.0
  auto v1 = core::Vec3{0.5, 0.5, 0.5};
  auto v2 = core::Vec3{1, 2, 3};

  REQUIRE(v0 == core::Vec3{0.0, 0.0, 0.0});
  REQUIRE(v1 <= v2);
  REQUIRE(v1 < v2);
  REQUIRE(v2 >= v1);
  REQUIRE(v2 > v1);

  REQUIRE((v2 += 1.0) == core::Vec3{2.0, 3.0, 4.0});
  REQUIRE((v2 -= 1) == core::Vec3{1.0, 2.0, 3.0});
  REQUIRE((v2 *= 2.0) == core::Vec3{2.0, 4.0, 6.0});
  REQUIRE((v2 /= 2.0) == core::Vec3{1.0, 2.0, 3.0});


  auto v3 = core::Vec3{10.0, 11.0, 12.0};
  // Addition
  REQUIRE((v2 + v3) == core::Vec3{11, 13, 15});
  REQUIRE((v3 + 1.1) == core::Vec3{11.1, 12.1, 13.1});
  REQUIRE((1.1 + v3) == core::Vec3{11.1, 12.1, 13.1});

  // Subtraction
  REQUIRE((v2 - v3) == core::Vec3{-9, -9, -9});
  REQUIRE((v3 - 5) == core::Vec3{5, 6, 7});
  REQUIRE((5 - v3) == core::Vec3{-5, -6, -7});

  // Multiplication
  REQUIRE((v2 * v3) == core::Vec3{10.0, 22, 36});
  REQUIRE((v3 * 2.0) == core::Vec3{20.0, 22.0, 24.0});
  REQUIRE((2.0 * v3) == core::Vec3{20.0, 22.0, 24.0});

  // Division
  auto r1 = (v2 / v3);
  REQUIRE(r1.x() == Catch::Approx(0.1));
  REQUIRE(r1.y() == Catch::Approx(0.1818182));
  REQUIRE(r1.z() == Catch::Approx(0.25));

  auto r2 = (v3 / 2);
  REQUIRE(r2.x() == 5);
  REQUIRE(r2.y() == 5.5);
  REQUIRE(r2.z() == 6);

  auto r3 = (2 / v3);
  REQUIRE(r3.x() == Catch::Approx(0.2));
  REQUIRE(r3.y() == Catch::Approx(0.1818182));
  REQUIRE(r3.z() == Catch::Approx(0.166667));


  // Length/Magnitude and unit vector
  auto v4 = core::Vec3{1, 1, 1};
  REQUIRE(v4.length_squared() == 3);
  REQUIRE(v4.length() == Catch::Approx(1.732050808));
  auto r4 = v4.unit_vector();
  REQUIRE(r4.x() == Catch::Approx(0.57735));
  REQUIRE(r4.y() == Catch::Approx(0.57735));
  REQUIRE(r4.z() == Catch::Approx(0.57735));

  auto v5 = core::Vec3{1, 2, 3};
  REQUIRE(v5.length_squared() == 14);
  REQUIRE(v5.length() == Catch::Approx(3.741657387));
  auto r5 = v5.unit_vector();
  REQUIRE(r5.x() == Catch::Approx(0.267261242));
  REQUIRE(r5.y() == Catch::Approx(0.534522484));
  REQUIRE(r5.z() == Catch::Approx(0.801783726));
}


// +-----------+
// | Ray tests |
// +-----------+

TEST_CASE("Ray", "[ray][core]")
{
  auto r0 = core::Ray{};
  REQUIRE(r0 == core::Ray{core::Vec3{0.0, 0.0, 0.0}, core::Vec3{0.0, 0.0, 0.0}});

  auto r1_origin = core::Vec3{0, 0, 0};
  auto r1_direction = core::Vec3{-1, 1, 0};
  auto r1 = core::Ray{r1_origin, r1_direction};

  REQUIRE(r1.origin() == core::Vec3{0, 0, 0});
  REQUIRE(r1.direction() == core::Vec3{-1, 1, 0});
  REQUIRE(r1.at(7) == core::Vec3{-7, 7, 0});


  auto r2_origin = core::Vec3{-1, 2, 3.5};
  auto r2_direction = core::Vec3{0.1, 10, 5.1};
  auto r2 = core::Ray{r2_origin, r2_direction};

  REQUIRE(r2.origin() == core::Vec3{-1, 2, 3.5});
  REQUIRE(r2.direction() == core::Vec3{0.1, 10, 5.1});

  auto p2 = r2.at(7);
  REQUIRE(p2.x() == Catch::Approx(-0.3));
  REQUIRE(p2.y() == Catch::Approx(72));
  REQUIRE(p2.z() == Catch::Approx(39.2));

  REQUIRE(r1 != r2);
}


// +--------------+
// | Sphere tests |
// +--------------+

TEST_CASE("Sphere", "[sphere][hitrecord][core]")
{
  auto const default_sphere = core::Sphere{};
  REQUIRE(default_sphere.centre() == core::Vec3{0.0, 0.0, 0.0});
  REQUIRE(default_sphere.radius() == 0.0);


  auto const sphere_centre = core::Vec3{0, 0, 0};
  double const sphere_radius = 2;
  auto const sphere = core::Sphere{sphere_centre, sphere_radius}; // Sphere centred at 0,0,0 with radius of 2

  auto const ray_origin = core::Vec3{-5, 0, 0};
  auto const ray_direction = core::Vec3{1, 0, 0};
  auto const ray = core::Ray{ray_origin, ray_direction}; // A ray originating at -5,0,0 moving in the x axis

  auto hit_record = core::HitRecord{};
  bool hit = sphere.hit(ray, -10, 10, hit_record); // Does it hit anyway between t == -10 and t == 10 along the ray path?
  REQUIRE(hit == true);

  auto const expected_hit_point = core::Vec3{-2, 0, 0};
  auto const expected_normal = core::Vec3{-1, 0, 0};
  double const expected_t = 3.0;
  bool const expected_front_face = true;
  auto const expected = core::HitRecord{expected_hit_point, expected_normal, expected_t, expected_front_face};
  REQUIRE(hit_record == expected);
}
