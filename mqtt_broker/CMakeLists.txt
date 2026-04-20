cmake_minimum_required(VERSION 3.30)
project(hh-display)

set(SRC "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INC "${CMAKE_CURRENT_SOURCE_DIR}/include")

add_executable(
  mqtt_broker 
  ${SRC}/main.cpp

  # Network
  ${SRC}/network/network_manager.cpp

  # MQTT
  ${SRC}/mqtt/mqtt_fixed_header.cpp
)

target_include_directories(mqtt_broker PRIVATE ${INC})
