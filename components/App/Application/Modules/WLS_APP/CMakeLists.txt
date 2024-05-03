# This file was automatically generated for projects
# without default 'CMakeLists.txt' file.

FILE(GLOB_RECURSE wls_task *.c utilities/*.c objects/*.c)
list(FILTER wls_task EXCLUDE REGEX "Test")

if (CONFIG_ANJAY_SECURITY_MODE_CERTIFICATES)
     set(Embedded_cert "../server_cert.der" "../client_cert.der" "../client_key.der")
else()
     set(Embedded_cert "")
endif()

idf_component_register(SRCS ${wls_task}
                       INCLUDE_DIRS "include" "utilities" "objects"
                       REQUIRES hal_ports Safe_Time Safe_Mem Panic Safe_Trace RTOS Internal_Comms Anjay-esp-idf)

