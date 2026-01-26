#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "./../src/renderlib/Framebuffer.hpp"

TEST_CASE( "clear buffer" ){
    Framebuffer f(20, 20);
    color red(1.0, 0, 0);
    color green(0, 1.0, 0);
    f.clearToColor(red);
    f.exportAsPNG("red_test.png");
    f.clearToHorizontalGradient(red, green);
    f.exportAsPNG("red_green_h_test.png");
    f.clearToVerticalGradient(red, green);
    f.exportAsPNG("red_green_v_test.png");
    REQUIRE(true);
}