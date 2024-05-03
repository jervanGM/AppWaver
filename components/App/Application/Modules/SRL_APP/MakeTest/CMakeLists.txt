# This file was automatically generated for projects
# without default 'CMakeLists.txt' file.
cmake_minimum_required(VERSION 3.5)
project("UnityTest" VERSION 1.0 LANGUAGES C)

# Define una variable CMake para activar o desactivar la macro condicional
option(FFF_ENABLE "Enable my macro" OFF)
option(DISABLE_TRACES "Enable my macro" OFF)

# Define la macro condicional basada en la variable CMake
if(FFF_ENABLE)
    add_definitions(-DFAKE_FUNC)
endif()

if(DISABLE_TRACES)
    add_definitions(-DSECURE_TRACES)
endif()

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_STANDARD 11)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

set(ROOT ../../../../../..)
# Include source files directories
file(GLOB TEST_SOURCES 
../Test/*.c
../*.c)

# Create executable
add_executable(test_suite ${TEST_SOURCES})

target_include_directories(test_suite PUBLIC
    ../include
    ${ROOT}/test_fwk/FFF
)

file(GLOB LIB_SOURCE_FILES
    ${ROOT}/test_fwk/Unity/src/unity.c
    ${ROOT}/lib/Safe_Trace/safe_trace_impl.c
    ${ROOT}/lib/Safe_Mem/safe_memory_impl.c
    ${ROOT}/lib/Safe_Time/safe_timer.c
    ${ROOT}/lib/Safe_Time/Test/mock/*.c
    ${ROOT}/lib/Panic/assert_panic_impl_pc.c
    ${ROOT}/lib/RTOS/rtos_pc.c
    ${ROOT}/components/App/HAL/hal_ports/*.c
    ${ROOT}/components/App/HAL/hal_ports/Test/mock/*.c
    ${ROOT}/components/App/Application/Modules/Internal_Comms/*.c
    ${ROOT}/lib/test_lib/*.c
)

# Add library directories
add_library(lib STATIC ${LIB_SOURCE_FILES})

target_include_directories(lib PUBLIC
    ${ROOT}/test_fwk/Unity/src
    ${ROOT}/lib/Common_Types
    ${ROOT}/lib/Common
    ${ROOT}/lib/Safe_Trace/include
    ${ROOT}/lib/Safe_Mem/Test/include
    ${ROOT}/lib/Safe_Time/Test/include
    ${ROOT}/lib/Panic/include
    ${ROOT}/lib/RTOS/include
    ${ROOT}/components/App/HAL/hal_ports/include
    ${ROOT}/components/App/HAL/hal_interfaces
    ${ROOT}/components/App/HAL/hal_ports/Test/include
    ${ROOT}/componnets/App/HAL/hal_ports/Test/include
    ${ROOT}/lib/test_lib
    ${ROOT}/components/App/Application/Modules/Internal_Comms/include
    ${ROOT}/components/App/Application/Modules/WLS_APP/include
    ${ROOT}/components/App/Application/Modules/ANA_APP/include
    ${ROOT}/components/App/Application/Modules/BTN_APP/include
    ${ROOT}/components/App/Application/Modules/IND_APP/include
    ${ROOT}/components/App/Application/Modules/PW_APP/include
    ${ROOT}/components/App/Application/Modules/MEM_APP/include
    ../include
)

# Link sources with libraries
target_link_libraries(test_suite lib)

# Add suite to CTest test runner
add_test(test_runner test_suite)


