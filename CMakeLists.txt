cmake_minimum_required (VERSION 2.8)
project (OpenWorld)

option(tests "Build the module tests." ON)

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

find_package(SDL_net REQUIRED)
find_package(SDL_image REQUIRED)
find_package(PNG REQUIRED)
find_package(SDL_ttf 2.0.8 REQUIRED)

pkg_check_modules( PANGOCAIRO REQUIRED pangocairo>=1.14.8 )
pkg_check_modules( FONTCONFIG REQUIRED fontconfig>=2.4.1 )

pkg_search_module( pangocairo required)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)

#find_package(SDL2Net REQUIRED)

SET(EXTRA_LIBS ${GLFW_LDFLAGS_OTHER})
add_definitions(${GLFW_CFLAGS_OTHER})

ADD_DEFINITIONS(
    -std=c++14 # Or -std=c++0x
    # Other flags
)


INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})

include_directories( ${OPENGL_INCLUDE_DIRS} )
include_directories( ${GLFW_INCLUDE_DIRS} )
include_directories( ${GLEW_INCLUDE_DIRS} )
include_directories( ${GLM_INCLUDE_DIRS} )
include_directories( ${SDL2_INCLUDE_DIRS} )
include_directories( ${PANGOCAIRO_INCLUDE_DIRS} )

include_directories( include )

set(SOURCE
    ${SOURCE}
    src/TerrainPatch.cpp
    src/ShaderLibrary.cpp
    src/Shader.cpp
    src/Renderer.cpp
    src/model.cpp
    src/SceneNode.cpp
    src/AssetLibrary.cpp
    src/Camera.cpp
    src/NetworkManager.cpp
    src/CubeMesh.cpp
    src/texturemanager.cpp
    src/texture.cpp
    )
    
set(HEADERS
    ${HEADERS}
    include/TerrainPatch.h
    include/ShaderLibrary.h
    include/Shader.h
    include/Renderer.h
    include/Model.h
    include/SceneNode.h
    include/AssetLibrary.h
    include/Camera.h
    include/NetworkManager.h
    include/CubeMesh.h
    include/texturemanager.h
    include/texture.h
    include/common.h
    )

ADD_LIBRARY( Hodhr ${SOURCE} ${HEADERS})

ADD_EXECUTABLE(OpenWorld 
    src/main.cpp 
    )

if(${tests})

	ADD_EXECUTABLE(testNetwork
		tests/test_network.cpp
		)

add_executable(testFonts
	tests/test_fonts.cpp
	)
endif()

TARGET_LINK_LIBRARIES(OpenWorld ${SDL2_LIBRARIES})
TARGET_LINK_LIBRARIES(OpenWorld ${GLFW_LIBRARIES})
TARGET_LINK_LIBRARIES(OpenWorld ${GLEW_LIBRARY})
TARGET_LINK_LIBRARIES(OpenWorld ${EXTRA_LIBS})
TARGET_LINK_LIBRARIES(OpenWorld ${OPENGL_LIBRARIES})
TARGET_LINK_LIBRARIES(OpenWorld Hodhr)

TARGET_LINK_LIBRARIES(testNetwork Hodhr)
TARGET_LINK_LIBRARIES(testNetwork 
				  ${SDL2_LIBRARIES}
				  ${SDLNET_LIBRARY})

target_link_libraries(testFonts
                        Hodhr
			${PANGOCAIRO_LIBRARIES})
