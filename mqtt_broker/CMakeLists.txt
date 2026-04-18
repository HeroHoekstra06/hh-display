cmake_minimum_required(VERSION 3.30)
project(hh-display)

set(SRC "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INC "${CMAKE_CURRENT_SOURCE_DIR}/include")

add_executable(
  mqtt_broker 
  ${SRC}/main.cpp
  ${SRC}/network/network_manager.cpp
)

target_include_directories(mqtt_broker PRIVATE ${INC})
