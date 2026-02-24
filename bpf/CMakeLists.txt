cmake_minimum_required(VERSION 3.20)
project(execguard_bpf_loader LANGUAGES CXX)

add_library(execguard_bpf_loader
    loader/bpf_loader.cpp
)

target_include_directories(execguard_bpf_loader PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
