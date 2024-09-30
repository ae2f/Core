add_executable(test_allocator "main.c")

target_link_libraries(test_allocator Core)
add_test(NAME test_allocator COMMAND test_allocator)