cmake_minimum_required(VERSION 3.16)
project(Cerraria CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(assimp REQUIRED)
find_package(Freetype REQUIRED)

add_library(glad STATIC external/glad/src/glad.c)
target_include_directories(glad PUBLIC external/glad/include)

add_executable(Cerraria src/core/main.cpp
    src/core/application.cpp
    include/core/application.h
    include/core/constants.h
    include/core/player.h
    src/core/player.cpp
    src/core/shader.cpp
    include/core/shader.h)
target_include_directories(Cerraria PRIVATE include external/stb)
target_link_libraries(Cerraria PRIVATE
    glad
    glfw
    OpenGL::GL
    glm::glm
    assimp::assimp
    Freetype::Freetype
)

target_compile_options(Cerraria PRIVATE)

target_compile_definitions(Cerraria PRIVATE ASSETS_DIR="${CMAKE_SOURCE_DIR}/assets/")

if(APPLE)
    target_compile_definitions(Cerraria PRIVATE GL_SILENCE_DEPRECATION)
endif()
