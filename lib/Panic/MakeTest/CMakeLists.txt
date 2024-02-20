# This file was automatically generated for projects
# without default 'CMakeLists.txt' file.
cmake_minimum_required(VERSION 3.5)
project("UnityTest" VERSION 1.0 LANGUAGES C)


set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_STANDARD 11)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

# Include source files directories
file(GLOB TEST_SOURCES 
../Test/*.c
../assert_panic_impl_pc.c)

# Create executable
add_executable(test_suite ${TEST_SOURCES})

target_include_directories(test_suite PUBLIC
    ../include
)

# Add library directories
add_library(lib STATIC
    ../../../test_fwk/Unity/src/unity.c
    ../../test_lib/panic_mock.c
)

target_include_directories(lib PUBLIC
    ../../../test_fwk/Unity/src
    ../../Common_Types
    ../../test_lib
)

# Link sources with libraries
target_link_libraries(test_suite lib)

# Add suite to CTest test runner
add_test(test_runner test_suite)


