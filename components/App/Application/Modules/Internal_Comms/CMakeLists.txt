# This file was automatically generated for projects
# without default 'CMakeLists.txt' file.

FILE(GLOB_RECURSE internal_comms *.c)
list(FILTER internal_comms EXCLUDE REGEX "Test")

idf_component_register(SRCS ${internal_comms}
                       INCLUDE_DIRS "include" 
                                    "../ANA_APP/include"
                                    "../WLS_APP/include"
                                    "../BTN_APP/include"
                                    "../IND_APP/include"
                                    "../PW_APP/include"
                                    "../MEM_APP/include"
                                    "../SRL_APP/include"
<<<<<<< HEAD
                                    "../BUS_APP/include"
                                    "../ACC_IT_APP/include"
=======
>>>>>>> 580f3ba01581a2c652de2ce061dcf930e0026a99
                       REQUIRES RTOS Safe_Time Safe_Trace)

