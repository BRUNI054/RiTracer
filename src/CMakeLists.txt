add_library (cs4212-util
  ArgumentParsing.cpp ArgumentParsing.h
  handleGraphicsArgs.cpp handleGraphicsArgs.h
  model_obj.cpp model_obj.h
)
target_compile_definitions(cs4212-util PUBLIC HAS_GLM)
target_link_libraries(cs4212-util PRIVATE Boost::program_options)
target_link_libraries(cs4212-util PUBLIC glm::glm)

add_library (render-lib
  renderlib/vec3.hpp
  renderlib/framebuffer.hpp
  renderlib/framebuffer.cpp
  renderlib/ray.hpp
  renderlib/camera.hpp
  renderlib/perspectiveCamera.hpp
  renderlib/shape.hpp
  renderlib/sphere.hpp
  renderlib/triangle.hpp
  renderlib/hitStruct.hpp
  renderlib/shader.hpp
  renderlib/shader.cpp
  renderlib/scene.hpp
  # renderlib/scene.cpp
  renderlib/normalShader.hpp
  renderlib/lambertian.hpp
  renderlib/polar.hpp
  renderlib/blinnPhong.hpp
  renderlib/mirror.hpp
)
target_link_libraries(render-lib cs4212-util)
target_link_libraries(render-lib ${Boost_PROGRAM_OPTIONS_LIBRARIES})
target_link_libraries(render-lib PNG::PNG)
target_link_libraries(render-lib ZLIB::ZLIB)

# add_executable(test_framebuffer
#   renderlib/test_framebuffer.cpp
# )
# target_link_libraries(test_framebuffer render-lib)

# add_executable(test_perspectiveCamera
#   renderlib/test_perspectiveCamera.cpp
# )
# target_link_libraries(test_perspectiveCamera render-lib)


# add_executable(test_sphere
#   renderlib/test_sphere.cpp
# )
# target_link_libraries(test_sphere render-lib)

# add_executable(test_triangle
#   renderlib/test_triangle.cpp
# )
# target_link_libraries(test_triangle render-lib)

# add_executable(test_sun
#   renderlib/test_sun.cpp
# )
# target_link_libraries(test_sun render-lib)

# add_executable(test_shader
#   renderlib/test_shader.cpp
# )
# target_link_libraries(test_shader render-lib)

# add_executable(test_antiAliasing
#   renderlib/test_antiAliasing.cpp
# )
# target_link_libraries(test_antiAliasing render-lib)

# add_executable(test_shadows
#   renderlib/test_shadows.cpp
# )
# target_link_libraries(test_shadows render-lib)

add_executable(main
  renderlib/main.cpp
)
target_link_libraries(main render-lib)