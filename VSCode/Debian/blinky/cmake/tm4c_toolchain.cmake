set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
include(CMakeForceCompiler)

#Set cross compilation information
set(CMAKE_SYSTEM_NAME Generic)
# set(CMAKE_SYSTEM_PROCESSOR arm)

# GCC toolchain prefix
set(TOOLCHAIN_PREFIX arm-none-eabi)

# set flags
set(TM4C_FLAGS "-mthumb -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=softfp")
set(TM4C_FLAGS "${TM4C_FLAGS} -O0 -ffunction-sections -fdata-sections ")
set(TM4C_FLAGS "${TM4C_FLAGS} -Wall -pedantic")
set(CMAKE_C_FLAGS "${TM4C_FLAGS} -std=c11" CACHE STRING "" FORCE)
set(CMAKE_EXE_LINKER_FLAGS "-Wl,-gc-sections,-T,${CMAKE_SOURCE_DIR}/tm4c.ld" CACHE STRING "" FORCE)

set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}-gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}-g++)

# Tivaware files
set(TIVAWARE_PATH "$ENV{TIVAWARE_PATH}")
include_directories(${TIVAWARE_PATH})

# Processor specific definitions
add_definitions(-DPART_TM4C123GH6PM)
add_definitions(-DTARGET_IS_TM4C123_RA1)
set(TIVAWARE_LIB "${TIVAWARE_PATH}/driverlib/gcc/libdriver.a")
