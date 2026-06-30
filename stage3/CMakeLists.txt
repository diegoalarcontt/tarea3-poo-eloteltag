cmake_minimum_required(VERSION 3.16)

project(stage3 VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

qt_add_executable(stage3
    main.cpp
    equipo.h
    cellular.h
    eloteltag.h
    tablet.h
    territory.h
    territory.cpp
    territoryview.h
    territoryview.cpp
    etnube.h
)

target_link_libraries(stage3 PRIVATE Qt6::Widgets)