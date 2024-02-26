# This file was automatically generated for projects
# without default 'CMakeLists.txt' file.

FILE(GLOB_RECURSE ana_task *.c)
list(FILTER ana_task EXCLUDE REGEX "Test")

idf_component_register(SRCS ${ana_task}
                       INCLUDE_DIRS "include"
                       REQUIRES hal_ports Safe_Time Safe_Mem Panic Safe_Trace RTOS Internal_Comms)

