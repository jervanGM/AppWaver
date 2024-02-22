cmake_minimum_required(VERSION 3.16.0)
include($ENV{IDF_PATH}/tools/cmake/project.cmake)

# Get a list of all folders within components directory
file(GLOB_RECURSE component_folders LIST_DIRECTORIES true components/*)

# Get a list of all folders within lib directory except those containing MakeTest
file(GLOB_RECURSE lib_folders LIST_DIRECTORIES true lib/*)
list(FILTER lib_folders EXCLUDE REGEX "lib/[^/]+/MakeTest")

# Iterate over each folder except MakeTest and look for CMakeLists.txt
foreach(component_folder ${component_folders})
    # Check if the folder contains CMakeLists.txt
    file(GLOB component_cmake "${component_folder}/CMakeLists.txt")
    if(component_cmake)
        # Add the folder as a component directory
        list(APPEND EXTRA_COMPONENT_DIRS ${component_folder})
        message("Component folder: ${component_folder}")
    endif()
endforeach()

foreach(lib_folder ${lib_folders})
    # Check if the folder contains CMakeLists.txt
    file(GLOB lib_cmake "${lib_folder}/CMakeLists.txt")
    if(lib_cmake)
        # Add the folder as a component directory
        list(APPEND EXTRA_COMPONENT_DIRS ${lib_folder})
        message("Lib folder: ${lib_folder}")
    endif()
endforeach()

project(AppWaver)


