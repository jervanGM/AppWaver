# This file was automatically generated for projects
# without default 'CMakeLists.txt' file.
cmake_minimum_required(VERSION 3.5)
project("UnityTest" VERSION 1.0 LANGUAGES C)

set(ROOT ../../../../../..)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_STANDARD 11)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

# Include source files directories
file(GLOB TEST_SOURCES 
../Test/*.c
../*.c)

# Create executable
add_executable(test_suite ${TEST_SOURCES})

target_include_directories(test_suite PUBLIC
    ../include
    ../../ANA_APP/include
    ../../BTN_APP/include
    ../../PW_APP/include
    ../../IND_APP/include
    ../../WLS_APP/include
    ../../MEM_APP/include
)

# Add library directories
file(GLOB LIB_SOURCE_FILES
    ${ROOT}/test_fwk/Unity/src/unity.c
    ${ROOT}/lib/Safe_Trace/safe_trace_impl.c
    ${ROOT}/lib/Safe_Mem/safe_memory_impl.c
    ${ROOT}/lib/Safe_Time/safe_timer.c
    ${ROOT}/lib/Panic/assert_panic_impl_pc.c
    ${ROOT}/lib/Safe_Time/Test/mock/*.c
    ${ROOT}/lib/test_lib/*.c
    ${ROOT}/lib/RTOS/rtos_pc.c
)

add_library(lib STATIC ${LIB_SOURCE_FILES})

target_include_directories(lib PUBLIC
    ${ROOT}/test_fwk/Unity/src
    ${ROOT}/lib/Common_Types
    ${ROOT}/lib/Common
    ${ROOT}/lib/Safe_Trace/include
    ${ROOT}/lib/Safe_Mem/Test/include
    ${ROOT}/lib/Safe_Time/Test/include
    ${ROOT}/lib/Panic/include
    ${ROOT}/lib/test_lib
    ${ROOT}/lib/RTOS/include
)

# Link sources with libraries
target_link_libraries(test_suite lib)

# Add suite to CTest test runner
add_test(test_runner test_suite)


