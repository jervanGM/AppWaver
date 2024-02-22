# This file was automatically generated for projects
# without default 'CMakeLists.txt' file.

FILE(GLOB_RECURSE control_task *.c)

idf_component_register(SRCS ${control_task}
                       INCLUDE_DIRS "include"
                       REQUIRES hal_ports Safe_Time Panic Safe_Trace RTOS Internal_Comms)

