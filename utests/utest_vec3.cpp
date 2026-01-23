#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "vec3tests/../../src/renderlib/vec3.hpp"

TEST_CASE( "Dot Product Test" )
{   
    vec3 vec1(1.2, 1.3, 1.4);
    vec3 vec2(2.4, 3.6, 4.8);
    float dotprod = vec1.dot(vec2);
    float actualAnswer = 14.28f;
    float eps = 1.0e-3;
    REQUIRE_THAT( dotprod, Catch::Matchers::WithinAbs(actualAnswer, eps));
}

TEST_CASE( "Cross Product Test" )
{   
    vec3 vec1(1.2, 1.3, 1.4);
    vec3 vec2(2.4, 3.6, 4.8);
    vec3 crossVec = vec1.cross(vec2);
    float actualX = 1.2f;
    float actualY = -2.4f;
    float actualZ = 1.2f;
    float eps = 1.0e-3;
    REQUIRE_THAT( crossVec.x(), Catch::Matchers::WithinAbs(actualX, eps));
    REQUIRE_THAT( crossVec.y(), Catch::Matchers::WithinAbs(actualY, eps));
    REQUIRE_THAT( crossVec.z(), Catch::Matchers::WithinAbs(actualZ, eps));
}

TEST_CASE( "Unit Vector Test" )
{   
    vec3 vec1(1.2, 1.3, 1.4);
    vec3 uVec = vec1.get_unit_vector();
    float actualX = 0.532f;
    float actualY = 0.576f;
    float actualZ = 0.621f;
    float eps = 1.0e-3;
    REQUIRE_THAT( uVec.x(), Catch::Matchers::WithinAbs(actualX, eps));
    REQUIRE_THAT( uVec.y(), Catch::Matchers::WithinAbs(actualY, eps));
    REQUIRE_THAT( uVec.z(), Catch::Matchers::WithinAbs(actualZ, eps));
}

TEST_CASE( "Float Operator Test" )
{   
    vec3 vec1(1.0, 1.0, 1.0);
    float tFloat = 3.4f;
    vec3 testMultEq = vec1;
    testMultEq *= tFloat;
    vec3 testMult = vec1 * tFloat;
    vec3 testMult2 = tFloat * vec1;
    vec3 realMult(3.4, 3.4, 3.4);
    vec3 testDivEq = vec1;
    testDivEq /= tFloat;
    vec3 testDiv = vec1 / tFloat;
    vec3 realDiv(0.294, 0.294,  0.294);
    float eps = 1.0e-3;
    REQUIRE_THAT( testMultEq.x(), Catch::Matchers::WithinAbs(realMult.x(), eps));
    REQUIRE_THAT( testMultEq.y(), Catch::Matchers::WithinAbs(realMult.y(), eps));
    REQUIRE_THAT( testMultEq.z(), Catch::Matchers::WithinAbs(realMult.z(), eps));
    REQUIRE_THAT( testMult.x(), Catch::Matchers::WithinAbs(realMult.x(), eps));
    REQUIRE_THAT( testMult.y(), Catch::Matchers::WithinAbs(realMult.y(), eps));
    REQUIRE_THAT( testMult.z(), Catch::Matchers::WithinAbs(realMult.z(), eps));
    REQUIRE_THAT( testMult2.x(), Catch::Matchers::WithinAbs(realMult.x(), eps));
    REQUIRE_THAT( testMult2.y(), Catch::Matchers::WithinAbs(realMult.y(), eps));
    REQUIRE_THAT( testMult2.z(), Catch::Matchers::WithinAbs(realMult.z(), eps));
    REQUIRE_THAT( testDivEq.x(), Catch::Matchers::WithinAbs(realDiv.x(), eps));
    REQUIRE_THAT( testDivEq.y(), Catch::Matchers::WithinAbs(realDiv.y(), eps));
    REQUIRE_THAT( testDivEq.z(), Catch::Matchers::WithinAbs(realDiv.z(), eps));
    REQUIRE_THAT( testDiv.x(), Catch::Matchers::WithinAbs(realDiv.x(), eps));
    REQUIRE_THAT( testDiv.y(), Catch::Matchers::WithinAbs(realDiv.y(), eps));
    REQUIRE_THAT( testDiv.z(), Catch::Matchers::WithinAbs(realDiv.z(), eps));
}

TEST_CASE( "Vector Operator Test" )
{   
    vec3 vec1(1.0, 1.0, 1.0);
    vec3 vec2(2.0, 2.0, 2.0);
    vec3 testMult = vec1 * vec2;
    vec3 realMult(2.0, 2.0, 2.0);
    vec3 testAddEq = vec1;
    testAddEq += vec2;
    vec3 testAdd = vec1 + vec2;
    vec3 realAdd(3.0, 3.0, 3.0);
    vec3 testSub = vec2 - vec1;
    vec3 realSub(1.0, 1.0, 1.0);

    float eps = 1.0e-3;
    REQUIRE_THAT( testMult.x(), Catch::Matchers::WithinAbs(realMult.x(), eps));
    REQUIRE_THAT( testMult.y(), Catch::Matchers::WithinAbs(realMult.y(), eps));
    REQUIRE_THAT( testMult.z(), Catch::Matchers::WithinAbs(realMult.z(), eps));
    REQUIRE_THAT( testAddEq.x(), Catch::Matchers::WithinAbs(realAdd.x(), eps));
    REQUIRE_THAT( testAddEq.y(), Catch::Matchers::WithinAbs(realAdd.y(), eps));
    REQUIRE_THAT( testAddEq.z(), Catch::Matchers::WithinAbs(realAdd.z(), eps));
    REQUIRE_THAT( testAdd.x(), Catch::Matchers::WithinAbs(realAdd.x(), eps));
    REQUIRE_THAT( testAdd.y(), Catch::Matchers::WithinAbs(realAdd.y(), eps));
    REQUIRE_THAT( testAdd.z(), Catch::Matchers::WithinAbs(realAdd.z(), eps));
    REQUIRE_THAT( testSub.x(), Catch::Matchers::WithinAbs(realSub.x(), eps));
    REQUIRE_THAT( testSub.y(), Catch::Matchers::WithinAbs(realSub.y(), eps));
    REQUIRE_THAT( testSub.z(), Catch::Matchers::WithinAbs(realSub.z(), eps));
}