# This file was automatically generated for projects
# without default 'CMakeLists.txt' file.

FILE(GLOB_RECURSE sw_config *.c)

idf_component_register(SRCS ${sw_config}
                       INCLUDE_DIRS "include"
                       REQUIRES hal_ports ANA_APP WLS_APP CTRL_APP BTN_APP BTN_DRV IND_APP PW_APP SRL_APP BUS_APP ACC_IT_DRV ACC_IT_APP RTOS Panic)

