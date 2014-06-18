cmake_minimum_required (VERSION 2.8)
project (OpenWorld)

set (Tutorial_VERSION_MAJOR 1)

INCLUDE(FindPkgConfig)

find_package(PkgConfig REQUIRED)
SET(CMAKE_MODULE_PATH /usr/share/cmake-2.8/Modules)
	
if(GLFW_FOUND)
    message(STATUS "Found GLFW")
endif(GLFW_FOUND)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)


find_package(GLM REQUIRED)


PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)

SET(EXTRA_LIBS ${GLFW_LDFLAGS_OTHER})
add_definitions(${GLFW_CFLAGS_OTHER})


INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})

include_directories( ${OPENGL_INCLUDE_DIRS} )
include_directories( ${GLFW_INCLUDE_DIRS} )
include_directories( ${GLEW_INCLUDE_DIRS} )
include_directories( ${GLM_INCLUDE_DIRS} )
include_directories( ${SDL2_INCLUDE_DIRS} )

ADD_EXECUTABLE(OpenWorld 
    src/main.cpp 
    src/TerrainPatch.h src/TerrainPatch.cpp
    src/ShaderLibrary.h src/ShaderLibrary.cpp
    src/Shader.h src/Shader.cpp
    )

TARGET_LINK_LIBRARIES(OpenWorld ${SDL2_LIBRARIES})
TARGET_LINK_LIBRARIES(OpenWorld ${GLFW_LIBRARIES})
TARGET_LINK_LIBRARIES(OpenWorld ${GLEW_LIBRARY})
TARGET_LINK_LIBRARIES(OpenWorld ${EXTRA_LIBS})
TARGET_LINK_LIBRARIES(OpenWorld ${OPENGL_LIBRARIES})
