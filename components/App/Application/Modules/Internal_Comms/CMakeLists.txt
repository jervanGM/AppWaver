# This file was automatically generated for projects
# without default 'CMakeLists.txt' file.

FILE(GLOB_RECURSE internal_comms *.c)

idf_component_register(SRCS ${internal_comms}
                       INCLUDE_DIRS "include" "../ANA_APP/include"
                       REQUIRES RTOS Safe_Time Safe_Trace)

