cmake_minimum_required(VERSION 3.5)
project(OpenGLK)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLM REQUIRED)
find_package(glfw3 REQUIRED)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})


        
add_executable(tugas02
        tugas02/main.cpp
        common/shader.cpp
        common/shader.hpp
        common/shape.cpp
        common/shape.h
        )
  

target_link_libraries(tugas02
        ${OPENGL_LIBRARY}
        glfw
        ${GLEW_LIBRARY}
        )
