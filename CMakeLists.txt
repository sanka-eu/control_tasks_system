cmake_minimum_required(VERSION 3.28)

project(control_tasks_system DESCRIPTION "Система контроля исполнения поручений" LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(src/application)