cmake_minimum_required(VERSION 3.20)
project(execguard_agent LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(execguard_agent_lib
    src/config/config_loader.cpp
    src/backend/backend_factory.cpp
    src/backend/lsm_backend.cpp
    src/backend/bpf_backend.cpp
    src/policy/policy_manager.cpp
    src/crypto/sha256.cpp
    src/logging/logger.cpp
    src/events/event_dispatcher.cpp
)

target_include_directories(execguard_agent_lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(execguard_agent
    src/main.cpp
)

target_link_libraries(execguard_agent PRIVATE execguard_agent_lib)
