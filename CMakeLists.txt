cmake_minimum_required(VERSION 3.1)

project(gf)

add_subdirectory(src)
add_subdirectory(tests)

enable_testing()
add_test(NAME gftests COMMAND tests)
