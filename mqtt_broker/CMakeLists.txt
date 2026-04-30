cmake_minimum_required(VERSION 3.30)
project(hh-display)

set(SRC "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INC "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(MAIN_SRC "${CMAKE_CURRENT_SOURCE_DIR}/../src")
set(MAIN_INC "${CMAKE_CURRENT_SOURCE_DIR}/../include")

add_executable(
  mqtt_broker 
  ${SRC}/main.cpp

  # Network
  ${SRC}/network/network_manager.cpp

  # MQTT
  ${MAIN_SRC}/mqtt/packet/mqtt_fixed_header.cpp
  ${MAIN_SRC}/mqtt/packet/mqtt_packet.cpp

  ${MAIN_SRC}/mqtt/packet/var_headers/mqtt_connack_var_header.cpp
  ${MAIN_SRC}/mqtt/packet/var_headers/mqtt_connect_var_header.cpp
  ${MAIN_SRC}/mqtt/packet/var_headers/mqtt_packetid_var_header.cpp
  ${MAIN_SRC}/mqtt/packet/var_headers/mqtt_publish_var_header.cpp
)

target_include_directories(mqtt_broker PRIVATE ${INC} ${MAIN_INC})
