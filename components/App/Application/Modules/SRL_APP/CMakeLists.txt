# This file was automatically generated for projects
# without default 'CMakeLists.txt' file.

FILE(GLOB_RECURSE srl_task *.c)
list(FILTER srl_task EXCLUDE REGEX "Test")

idf_component_register(SRCS ${srl_task}
                       INCLUDE_DIRS "include"
                       REQUIRES hal_ports Safe_Time Safe_Mem Panic Safe_Trace RTOS Internal_Comms)

