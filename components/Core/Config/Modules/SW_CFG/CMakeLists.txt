# This file was automatically generated for projects
# without default 'CMakeLists.txt' file.

FILE(GLOB_RECURSE sw_config *.c)

idf_component_register(SRCS ${sw_config}
                       INCLUDE_DIRS "include"
                       REQUIRES hal_ports ANA_APP CTRL_APP RTOS)

