include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable (glfwExample
  glfwExample.cpp 
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

add_executable (moveTriWithModel
    moveTriWithModelAndPersp.cpp
    GLSL.cpp GLSL.h
)
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

add_executable (openGL_D6
    openGL_D6.cpp
    GLSL.cpp GLSL.h
)

target_link_libraries (openGL_D6 PRIVATE GLEW::GLEW)
target_link_libraries (openGL_D6 PRIVATE glfw)

if(APPLE)
    target_link_libraries(openGL_D6 PRIVATE
        "-framework OpenGL"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
    )
else()
    target_link_libraries(openGL_D6 PRIVATE OpenGL::GL)
endif()

target_link_libraries (openGL_D6 PRIVATE PNG::PNG)
target_link_libraries (openGL_D6 PRIVATE ZLIB::ZLIB)
target_link_libraries (openGL_D6 PRIVATE render-lib)

add_executable (framebuffer
  openGL_framebuffer.cpp 
  GLSL.cpp GLSL.h
)
target_link_libraries (framebuffer PRIVATE GLEW::GLEW)
target_link_libraries (framebuffer PRIVATE glfw)

if(APPLE)
    target_link_libraries(framebuffer PRIVATE
        "-framework OpenGL"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
    )
else()
    target_link_libraries(framebuffer PRIVATE OpenGL::GL)
endif()

target_link_libraries (framebuffer PRIVATE PNG::PNG)
target_link_libraries (framebuffer PRIVATE ZLIB::ZLIB)


add_executable (D6
    openGL_D6.cpp
    GLSL.cpp GLSL.h
)

target_link_libraries (D6 PRIVATE GLEW::GLEW)
target_link_libraries (D6 PRIVATE glfw)

if(APPLE)
    target_link_libraries(D6 PRIVATE
        "-framework OpenGL"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
    )
else()
    target_link_libraries(D6 PRIVATE OpenGL::GL)
endif()

target_link_libraries (D6 PRIVATE PNG::PNG)
target_link_libraries (D6 PRIVATE ZLIB::ZLIB)
target_link_libraries (D6 PRIVATE render-lib)

add_executable (objTest
  openGL_objTest.cpp 
  GLSL.cpp GLSL.h
)
target_link_libraries (objTest PRIVATE GLEW::GLEW)
target_link_libraries (objTest PRIVATE glfw)
target_link_libraries (objTest PRIVATE tinyOBJ)

if(APPLE)
    target_link_libraries(objTest PRIVATE
        "-framework OpenGL"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
    )
else()
    target_link_libraries(objTest PRIVATE OpenGL::GL)
endif()

target_link_libraries (objTest PRIVATE PNG::PNG)
target_link_libraries (objTest PRIVATE ZLIB::ZLIB)

