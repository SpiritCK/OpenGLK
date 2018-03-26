cmake_minimum_required(VERSION 3.5)
project(OpenGLK)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(tutorial01
        tutorial01/main.cpp
        )
        
add_executable(example01
        example01/src/main.cpp
        commons/shader.cpp
        commons/shader.hpp
        )

target_link_libraries(tutorial01
        ${OPENGL_LIBRARY}
        glfw
        ${GLEW_LIBRARY}
        )

target_link_libraries(example01
        ${OPENGL_LIBRARY}
        glfw
        ${GLEW_LIBRARY}
        )
