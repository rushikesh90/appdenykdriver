cmake_minimum_required(VERSION 3.20)
project(execguard_tests LANGUAGES CXX)

add_executable(unit_test_policy unit/test_policy.cpp)
add_executable(unit_test_sha256 unit/test_sha256.cpp)
add_executable(integration_test_lsm_exec integration/test_lsm_exec.cpp)
add_executable(integration_test_bpf_exec integration/test_bpf_exec.cpp)
