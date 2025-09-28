cmake_minimum_required(VERSION 3.25.1)

# set(CMAKE_VERBOSE_MAKEFILE on)  # uncomment for CMake debugging

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/tm4c_toolchain.cmake)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_BUILD_TYPE Debug CACHE STRING "" FORCE)

include(Firmware)
# include(cmake/tm4c_toolchain.cmake)

project(BLINKY_RGB)

#Source files
file(GLOB_RECURSE SOURCES "src/*.c" 
    "${TIVAWARE_PATH}/driverlib/sysctl.c" 
    "${TIVAWARE_PATH}/driverlib/gpio.c"
)
add_executable(${PROJECT_NAME}.axf ${SOURCES})
add_raw_binary(${PROJECT_NAME}.bin ${PROJECT_NAME}.axf)

target_include_directories(${PROJECT_NAME}.axf PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)

target_link_libraries(${PROJECT_NAME}.axf)
