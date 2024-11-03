cmake_minimum_required(VERSION 3.29)
project(especializacao_2024_event_manager_system)

set(CMAKE_CXX_STANDARD 20)

add_executable(especializacao_2024_event_manager_system
        main.cpp
        EventManagerSystem.cpp)


option(ENABLE_NO_USER_INPUT "Program will automatically add 10 events, handover 5 of them, print the event list and exit without user interaction" OFF)

if(ENABLE_NO_USER_INPUT)
    target_compile_definitions(especializacao_2024_event_manager_system PRIVATE NO_USER_INPUT)
endif()
