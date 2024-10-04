link_libraries(Core)

add_executable(ae2f_Core_Test01 "test01/main.c")
add_test(NAME ae2f_Core_Test01 COMMAND ae2f_Core_Test01)