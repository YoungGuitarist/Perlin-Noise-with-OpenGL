cmake_minimum_required(VERSION 3.10)
project(MyOpenGLProject)

set(CMAKE_CXX_STANDARD 17)

if(UNIX AND NOT APPLE)  # Если система Linux
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GLFW REQUIRED glfw3)
    include_directories(${GLFW_INCLUDE_DIRS})

    find_path(GLAD_INCLUDE_DIR glad/glad.h PATH_SUFFIXES include)
    if(NOT GLAD_INCLUDE_DIR)
        message(STATUS "Glad not found in system, using local version")
        include_directories(libs/glad/include)
        file(GLOB GLAD_SOURCES "libs/glad/src/glad.c")
    else()
        message(STATUS "Found Glad in system: ${GLAD_INCLUDE_DIR}")
        include_directories(${GLAD_INCLUDE_DIR})
        set(GLAD_SOURCES "")
    endif()

    add_executable(MyApp main.cpp ${GLAD_SOURCES})
    target_link_libraries(MyApp ${GLFW_LIBRARIES} GL)

else()
    add_subdirectory(libs/glfw-3.4)
    set(GLFW_LIBRARY glfw)

    include_directories(libs/glad/include)
    file(GLOB GLAD_SOURCES "libs/glad/src/glad.c")

    add_executable(MyApp main.cpp ${GLAD_SOURCES})
    target_link_libraries(MyApp ${GLFW_LIBRARY} opengl32)
endif()