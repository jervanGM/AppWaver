# This file was automatically generated for projects
# without default 'CMakeLists.txt' file.

FILE(GLOB_RECURSE tmr_lib *.c)

idf_component_register(SRCS ${tmr_lib}
                       INCLUDE_DIRS "include"
                                    "../Common"
                                    "../Common_Types"
                       REQUIRES esp_timer)

