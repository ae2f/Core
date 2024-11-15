link_libraries(Core)
project(CoreTest)

add_executable(${PROJECT_NAME} "a.cpp" "main.c")
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})