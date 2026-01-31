#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "./renderlib/ray.hpp"

TEST_CASE( "Dot Product Test" )
{   
    vec3 vec1(1.2, 1.3, 1.4);
    vec3 vec2(2.4, 3.6, 4.8);
    float dotprod = vec1.dot(vec2);
    float actualAnswer = 14.28f;
    float eps = 1.0e-3;
    REQUIRE_THAT( dotprod, Catch::Matchers::WithinAbs(actualAnswer, eps));
}

