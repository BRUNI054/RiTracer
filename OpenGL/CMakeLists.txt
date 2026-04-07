include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable (glfwExample
  glfwExample.cpp 
  GLSL.cpp GLSL.h
)

add_executable (moveTriWithModel
    moveTriWithModelAndPersp.cpp
    GLSL.cpp GLSL.h
)

target_link_libraries (glfwExample PRIVATE GLEW::GLEW)
target_link_libraries (glfwExample PRIVATE glfw)

if(APPLE)
    target_link_libraries(glfwExample PRIVATE
        "-framework OpenGL"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
    )
else()
    target_link_libraries(glfwExample PRIVATE OpenGL::GL)
endif()

target_link_libraries (glfwExample PRIVATE PNG::PNG)
target_link_libraries (glfwExample PRIVATE ZLIB::ZLIB)

target_link_libraries (moveTriWithModel PRIVATE GLEW::GLEW)
target_link_libraries (moveTriWithModel PRIVATE glfw)

if(APPLE)
    target_link_libraries(moveTriWithModel PRIVATE
        "-framework OpenGL"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
    )
else()
    target_link_libraries(moveTriWithModel PRIVATE OpenGL::GL)
endif()

target_link_libraries (moveTriWithModel PRIVATE PNG::PNG)
target_link_libraries (moveTriWithModel PRIVATE ZLIB::ZLIB)

