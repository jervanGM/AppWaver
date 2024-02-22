# This file was automatically generated for projects
# without default 'CMakeLists.txt' file.

FILE(GLOB_RECURSE rtos_lib rtos.c)

idf_component_register(SRCS ${rtos_lib}
                       INCLUDE_DIRS "include" "../Common_Types"
                       REQUIRES Panic)

