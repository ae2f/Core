add_executable(xtest_0 "xmain.cpp")

target_link_libraries(xtest_0 Core)
add_test(NAME xtest_0 COMMAND xtest_0)