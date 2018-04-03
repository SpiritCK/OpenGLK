cmake_minimum_required(VERSION 3.5)
project(OpenGLK)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLM REQUIRED)
find_package(glfw3 REQUIRED)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(tugas01
        tugas01/main.cpp
        common/shader.cpp
        common/shader.hpp
        )
        
add_executable(tugas02
        tugas02/main.cpp
        common/shader.cpp
        common/shader.hpp
        common/shape.cpp
        common/shape.h
        )
        
add_executable(tugas02_test
        tugas02_test/main.cpp
        common/shader.cpp
        common/shader.hpp
        common/polygon.cpp
        common/polygon.h
        common/controls.hpp
        common/controls.cpp
        )
        
add_executable(tutorial01
        tutorial01/main.cpp
        )
        
add_executable(example01
        example01/src/main.cpp
        common/shader.cpp
        common/shader.hpp
        )
add_executable(tutorial04
        tutorial04/tutorial04.cpp
        common/shader.cpp
        common/shader.hpp
        )

target_link_libraries(tugas01
        ${OPENGL_LIBRARY}
        glfw
        ${GLEW_LIBRARY}
        )

target_link_libraries(tugas02
        ${OPENGL_LIBRARY}
        glfw
        ${GLEW_LIBRARY}
        )

target_link_libraries(tugas02_test
        ${OPENGL_LIBRARY}
        glfw
        ${GLEW_LIBRARY}
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
        
target_link_libraries(tutorial04
        ${OPENGL_LIBRARY}
        glfw
        ${GLEW_LIBRARY}
        )

