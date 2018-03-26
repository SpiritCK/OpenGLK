# OpenGLK
## Libraries required
- cmake
- make
- g++
- libx11-dev
- libxi-dev
- libgl1-mesa-dev
- libglu1-mesa-dev
- libxrandr-dev
- libxext-dev
- libxcursor-dev
- libxinerama-dev
- libxi-dev
- libglew-dev
- libglfw3-dev
- libglm-dev

For Linux user, just use
`sudo apt-get install cmake make g++ libx11-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxrandr-dev libxext-dev libxcursor-dev libxinerama-dev libxi-dev libglew-dev libglfw3-dev libglm-dev`

## Compilation
`./compile.sh`

### Compile error
If you find this error:
```By not providing "FindGLM.cmake" in CMAKE_MODULE_PATH this project has asked CMake to find a package configuration file provided by "GLM", but CMake did not find one.

Could not find a package configuration file provided by "GLM" with any of the following names:

    GLMConfig.cmake
    glm-config.cmake

Add the installation prefix of "GLM" to CMAKE_PREFIX_PATH or set "GLM_DIR" to a directory containing one of the above files.  If "GLM" provides a separate development package or SDK, be sure it has been installed.
```
Follow this step

1. Open terminal and go to /usr/share/cmake-x.x/Modules
2. `sudo vim FindGLM.cmake`
3. press `i` and copy paste this code
```
#
# Find GLM
#
# Try to find GLM : OpenGL Mathematics.
# This module defines 
# - GLM_INCLUDE_DIRS
# - GLM_FOUND
#
# The following variables can be set as arguments for the module.
# - GLM_ROOT_DIR : Root library directory of GLM 
#
# References:
# - https://github.com/Groovounet/glm/blob/master/util/FindGLM.cmake
# - https://bitbucket.org/alfonse/gltut/src/28636298c1c0/glm-0.9.0.7/FindGLM.cmake
#

# Additional modules
include(FindPackageHandleStandardArgs)

if (WIN32)
	# Find include files
	find_path(
		GLM_INCLUDE_DIR
		NAMES glm/glm.hpp
		PATHS
		$ENV{PROGRAMFILES}/include
		${GLM_ROOT_DIR}/include
		DOC "The directory where glm/glm.hpp resides")
else()
	# Find include files
	find_path(
		GLM_INCLUDE_DIR
		NAMES glm/glm.hpp
		PATHS
		/usr/include
		/usr/local/include
		/sw/include
		/opt/local/include
		${GLM_ROOT_DIR}/include
		DOC "The directory where glm/glm.hpp resides")
endif()

# Handle REQUIRD argument, define *_FOUND variable
find_package_handle_standard_args(GLM DEFAULT_MSG GLM_INCLUDE_DIR)

# Define GLM_INCLUDE_DIRS
if (GLM_FOUND)
	set(GLM_INCLUDE_DIRS ${GLM_INCLUDE_DIR})
endif()

# Hide some variables
mark_as_advanced(GLM_INCLUDE_DIR)
```
4. Press `Esc` > `":w"` > `":q"`
5. Try compile again

## How To Run
`./bin/[program_name]`

## Programs
- `tugas01`
