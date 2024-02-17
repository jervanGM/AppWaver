cmake_minimum_required(VERSION 3.16.0)
include($ENV{IDF_PATH}/tools/cmake/project.cmake)

# Get a list of all folders within components directory
file(GLOB_RECURSE component_folders LIST_DIRECTORIES true components/*)
file(GLOB_RECURSE lib_folders LIST_DIRECTORIES true lib/*)
# Iterate over each folder
foreach(component_folder ${component_folders})
    # Check if the folder contains .c files
    file(GLOB_RECURSE component_sources ${component_folder}/*.c)
    if(component_sources)
        # Add the folder as a component directory
        list(APPEND EXTRA_COMPONENT_DIRS ${component_folder})
        message("Component folder: ${component_folder}")
    endif()
endforeach()

foreach(lib_folder ${lib_folders})
    # Check if the folder contains .c files
    file(GLOB_RECURSE lib_sources ${lib_folder}/*.c)
    if(lib_sources)
        # Add the folder as a component directory
        list(APPEND EXTRA_COMPONENT_DIRS ${lib_folder})
        message("Lib folder: ${lib_folder}")
    endif()
endforeach()

project(AppWaver)

