# Encuentra el archivo fuente principal
FILE(GLOB_RECURSE app_sources main.c)

# Registra el componente con el archivo fuente principal y declara HW_CFG como dependencia
idf_component_register(SRCS ${app_sources}
                       INCLUDE_DIRS ".")
