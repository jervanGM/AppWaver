# This file was automatically generated for projects
# without default 'CMakeLists.txt' file.

FILE(GLOB_RECURSE panic_lib assert_panic_impl.c)

idf_component_register(SRCS ${panic_lib}
                       INCLUDE_DIRS "include")

