#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "./renderlib/ray.hpp"



TEST_CASE( "Base Constructor Test" )
{   
    float eps = 1.0e-3;

    ray r1 = ray();

    point zeros = point(0.0f, 0.0f, 0.0f);
    vec3 oneDirection = vec3(1.0f, 1.0f, 1.0f);

    REQUIRE_THAT( r1.origin().x(), Catch::Matchers::WithinAbs(zeros.x(), eps));
    REQUIRE_THAT( r1.origin().y(), Catch::Matchers::WithinAbs(zeros.y(), eps));
    REQUIRE_THAT( r1.origin().z(), Catch::Matchers::WithinAbs(zeros.z(), eps));

    REQUIRE_THAT( r1.direction().x(), Catch::Matchers::WithinAbs(oneDirection.x(), eps));
    REQUIRE_THAT( r1.direction().y(), Catch::Matchers::WithinAbs(oneDirection.y(), eps));
    REQUIRE_THAT( r1.direction().z(), Catch::Matchers::WithinAbs(oneDirection.z(), eps));
}

TEST_CASE("Special Constructor & Crazy Values Test")
{
    float eps = 1.0e-3;

    point wackoOrigin = point(30.93f, -64.23f, 96.7f);
    vec3 crazyDirection = vec3(48.6f, 934.3f, -65.968);
    ray r2 = ray(wackoOrigin, crazyDirection);

    REQUIRE_THAT( r2.origin().x(), Catch::Matchers::WithinAbs(wackoOrigin.x(), eps));
    REQUIRE_THAT( r2.origin().y(), Catch::Matchers::WithinAbs(wackoOrigin.y(), eps));
    REQUIRE_THAT( r2.origin().z(), Catch::Matchers::WithinAbs(wackoOrigin.z(), eps));

    REQUIRE_THAT( r2.direction().x(), Catch::Matchers::WithinAbs(crazyDirection.x(), eps));
    REQUIRE_THAT( r2.direction().y(), Catch::Matchers::WithinAbs(crazyDirection.y(), eps));
    REQUIRE_THAT( r2.direction().z(), Catch::Matchers::WithinAbs(crazyDirection.z(), eps));
}

TEST_CASE("'at' Function")
{
    float eps = 1.0e-3;

    ray r1 = ray();

    point zeros = point(0.0f, 0.0f, 0.0f);
    vec3 oneDirection = vec3(1.0f, 1.0f, 1.0f);

    point wackoOrigin = point(30.93f, -64.23f, 96.7f);
    vec3 crazyDirection = vec3(48.6f, 934.3f, -65.968);
    ray r2 = ray(wackoOrigin, crazyDirection);

    vec3 r1TrueAt = (1.0f * oneDirection) + zeros;
    REQUIRE_THAT( r1.at(1.0f).x(), Catch::Matchers::WithinAbs(r1TrueAt.x(), eps));
    REQUIRE_THAT( r1.at(1.0f).y(), Catch::Matchers::WithinAbs(r1TrueAt.y(), eps));
    REQUIRE_THAT( r1.at(1.0f).z(), Catch::Matchers::WithinAbs(r1TrueAt.z(), eps));

    vec3 r2TrueAt = (3.6f * crazyDirection) + wackoOrigin;
    REQUIRE_THAT( r2.at(3.6f).x(), Catch::Matchers::WithinAbs(r2TrueAt.x(), eps));
    REQUIRE_THAT( r2.at(3.6f).y(), Catch::Matchers::WithinAbs(r2TrueAt.y(), eps));
    REQUIRE_THAT( r2.at(3.6f).z(), Catch::Matchers::WithinAbs(r2TrueAt.z(), eps));
}
