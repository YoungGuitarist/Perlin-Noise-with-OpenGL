cmake_minimum_required(VERSION 3.10)
project(PerlinOpenGL)

set(CMAKE_CXX_STANDARD 17)

add_executable(PerlinOpenGL
    main.cpp
    glad/glad.c
)

include_directories(glad/include)

find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

include_directories(${GLFW_INCLUDE_DIRS})
target_link_libraries(PerlinOpenGL ${GLFW_LIBRARIES} ${OPENGL_LIBRARIES})