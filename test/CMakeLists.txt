# CppSharp
find_package(PkgConfig)
pkg_search_module(CPPUNIT cppunit)
if (NOT CPPUNIT_FOUND)
    message(FATAL_ERROR "Please install CppUnit development files")
endif ()

#Mangler sådan, at Ubuntu-C.ttf og map.txt bliver kopieret over i randsim.app

# Includes
include_directories(common simavr simavr/cores simavr/sim simavr/sim/avr)
include_directories(common /usr/local/include/)

add_subdirectory(simavr)
add_subdirectory(common)
add_subdirectory(unit_firmware)
add_subdirectory(component_firmware)
add_subdirectory(unit)
add_subdirectory(component)
add_subdirectory(system)
