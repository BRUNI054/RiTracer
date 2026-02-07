#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "./renderlib/sphere.hpp"

TEST_CASE( "Sphere Center Intersection Test" )
{   
    float eps = 1.0e-3;

    sphere s = sphere(vec3(0.0f,0.0f,-4.0f), 2.0f, color(0,0,1.0f));

    ray r = ray(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f));

    point zeros = point(0.0f, 0.0f, 0.0f);
    vec3 oneDirection = vec3(1.0f, 1.0f, 1.0f);

    REQUIRE(s.intersect(r));
}

TEST_CASE( "Sphere Arbitrary Intersection Test" )
{   
    float eps = 1.0e-3;

    sphere s = sphere(vec3(0.0f,0.0f,-4.0f), 2.0f, color(0,0,1.0f));

    ray r = ray(vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f));

    point zeros = point(0.0f, 0.0f, 0.0f);
    vec3 oneDirection = vec3(1.0f, 1.0f, 1.0f);

    REQUIRE(s.intersect(r));
}

TEST_CASE( "Sphere Edge Intersection Test" )
{   
    float eps = 1.0e-3;

    sphere s = sphere(vec3(0.0f,0.0f,-4.0f), 2.0f, color(0,0,1.0f));

    ray r = ray(vec3(0.0f, 2.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f));

    point zeros = point(0.0f, 0.0f, 0.0f);
    vec3 oneDirection = vec3(1.0f, 1.0f, 1.0f);

    REQUIRE(s.intersect(r));
}