# This file was automatically generated for projects
# without default 'CMakeLists.txt' file.
cmake_minimum_required(VERSION 3.5)
project("UnityTest" VERSION 1.0 LANGUAGES C)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_STANDARD 11)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
# Especifica la ruta al compilador MinGW

# Agrega Unity como una biblioteca estática
add_library(unity STATIC
    ../../../test_fwk/Unity/src/unity.c
)

# Incluye los directorios de inclusión de Unity
target_include_directories(unity PUBLIC
    ../../../test_fwk/Unity/src
)

# Incluye los archivos fuente del proyecto
file(GLOB PROJECT_SOURCES ../safe_trace_impl.c)

# Crea el ejecutable del proyecto
add_library(release ${PROJECT_SOURCES})

# Incluye los directorios de inclusión del proyecto
target_include_directories(release PUBLIC 
                        "../include"
                        "../../Common_Types")

# Incluye las pruebas de Unity Test Framework

# Incluye los archivos de prueba
file(GLOB TEST_SOURCES ../Test/*.c)

# Crea el ejecutable de pruebas
add_executable(test_suite ${TEST_SOURCES})

target_include_directories(test_suite PUBLIC 
                        "../../test_lib")

# Vincula el ejecutable de pruebas con Unity y el ejecutable del proyecto
target_link_libraries(test_suite release unity)

# Agrega un test
add_test(test_runner test_suite)


