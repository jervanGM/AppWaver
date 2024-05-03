# This file was automatically generated for projects
# without default 'CMakeLists.txt' file.

FILE(GLOB_RECURSE control_task *.c)
list(FILTER control_task EXCLUDE REGEX "Test")

idf_component_register(SRCS ${control_task}
                       INCLUDE_DIRS "include"
                       REQUIRES Safe_Time Safe_Mem Panic Safe_Trace RTOS Internal_Comms)
