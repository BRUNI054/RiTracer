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
  renderlib/Framebuffer.hpp
  renderlib/Framebuffer.cpp
)
target_link_libraries(render-lib cs4212-util)
target_link_libraries(render-lib ${Boost_PROGRAM_OPTIONS_LIBRARIES})
target_link_libraries(render-lib PNG::PNG)
target_link_libraries(render-lib ZLIB::ZLIB)

add_executable(test_framebuffer
  renderlib/test_framebuffer.cpp
)
target_link_libraries(test_framebuffer render-lib)

add_executable(test_perspectiveCamera
  renderlib/test_perspectiveCamera.cpp
)
target_link_libraries(test_perspectiveCamera render-lib)