cmake_minimum_required(VERSION 3.17)
project(lab1)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/Modules")
set(CMAKE_CXX_STANDARD 20)

find_package(GLFW REQUIRED)
include_directories(${GLFW_INCLUDE_DIR})
include_directories(glad)
include_directories(KHR)
include_directories(glm)

add_executable(lab1 main.cpp glad.c Shader.cpp Shader.h glm/glm.hpp glm/gtc/matrix_transform.hpp glm/gtc/type_ptr.hpp)

target_link_libraries(lab1 ${GLFW_LIBRARIES})
