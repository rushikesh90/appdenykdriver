cmake_minimum_required(VERSION 3.20)
project(appdenykdriver LANGUAGES C CXX)

add_subdirectory(agent)
add_subdirectory(bpf)
add_subdirectory(tests)
