# This file was automatically generated for projects
# without default 'CMakeLists.txt' file.

FILE(GLOB_RECURSE ana_task *.c)

idf_component_register(SRCS ${ana_task}
                       INCLUDE_DIRS "include"
                       REQUIRES hal_ports Safe_Time Panic Safe_Trace)

