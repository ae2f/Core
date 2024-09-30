add_executable(test_0 "main.c")

target_link_libraries(test_0 Core)
add_test(NAME test_0 COMMAND test_0)