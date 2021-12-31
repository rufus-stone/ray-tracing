#include <catch2/catch_all.hpp>

#include "vec3.hpp"


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
}
