if (APPLE)
    link_directories(/usr/local/lib)

    set(CMAKE_MACOSX_BUNDLE true)

    set_source_files_properties([map.txt PROPERTIES MACOSX_PACKAGE_LOCATION Resources/)

    file(COPY "map.txt" DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug/randsim.app/Contents/MacOS/)
    file(COPY "Fonts/Ubuntu-C.ttf" DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug/randsim.app/Contents/Resources/Fonts/)
endif()

# SDL2
if ("${CMAKE_SYSTEM_NAME}" STREQUAL "Emscripten")
    message("Using Emscripten")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s USE_SDL_TTF=2")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s WASM=1")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --embed-file map.txt --embed-file minimap.txt --embed-file Fonts/Ubuntu-C.ttf")
else()
    include(FindPkgConfig)
    pkg_search_module(SDL2 REQUIRED sdl2)
    pkg_search_module(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
    pkg_search_module(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)
endif()

# Resource files
file(COPY "Fonts" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
configure_file(map.txt map.txt COPYONLY)
configure_file(minimap.txt minimap.txt COPYONLY)

# Add mock definitions
add_definitions(-DMOCK)
add_definitions(-D__AVR_ATmega328P__)

# Target
include_directories(${CMAKE_CURRENT_SOURCE_DIR} Common UI SimObject)
add_executable(randsim Main.cpp SimObject/Drone.cpp UI/Minimap.cpp Fonts/Ubuntu-C.ttf map.txt Simulator.cpp Simulator.h UI/Renderer.cpp UI/Renderer.h UI/SdlRenderer.cpp UI/SdlRenderer.h SimObject/SimObject.cpp SimObject/SimObject.h SimObject/Block.cpp SimObject/Block.h Common/Vector2D.cpp Common/Vector2D.h SimObject/Sonar.cpp SimObject/Sonar.h Common/Ray.cpp Common/Ray.h SimObject/Laser.cpp SimObject/Laser.h UI/BlockBuilder.cpp UI/BlockBuilder.h)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS})
target_link_libraries(randsim nav fc kalman matrix map sonar ir laser ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES})
