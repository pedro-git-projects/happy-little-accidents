cmake_minimum_required(VERSION 3.14)

project(HappyLittleAccidentsServer LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS WebSockets)

add_executable(HappyLittleAccidentsServer
  main.cpp
  gamemanager.h
  gamemanager.cpp
  websockethandler.h
  websockethandler.cpp
  libs/uuid.h libs/uuid.cpp
)
target_link_libraries(HappyLittleAccidentsServer Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(HappyLittleAccidentsServer Qt6::WebSockets)

install(TARGETS HappyLittleAccidentsServer
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
