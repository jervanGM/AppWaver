# This file was automatically generated for projects
# without default 'CMakeLists.txt' file.

FILE(GLOB_RECURSE trace_lib safe_trace_impl.c)

idf_component_register(SRCS ${trace_lib}
                       INCLUDE_DIRS "include"
                                    "../Common_Types")

