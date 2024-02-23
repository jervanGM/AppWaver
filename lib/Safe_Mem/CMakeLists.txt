# This file was automatically generated for projects
# without default 'CMakeLists.txt' file.

FILE(GLOB_RECURSE mem_lib safe_memory_impl.c)

idf_component_register(SRCS ${mem_lib}
                       INCLUDE_DIRS "include"
                       REQUIRES Safe_Trace)

