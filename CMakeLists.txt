cmake_minimum_required(VERSION 3.28)
project(Project_2___Cogwork_Engineers LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.1.0
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(Project_2___Cogwork_Engineers
        src/bPlus.cpp
        src/bPlus.h
        src/DataHeap.h
        src/DataPoint.h
        src/FeatureLog.cpp
        src/FeatureLog.h
        src/MenuUI.cpp
        src/MenuUI.h
        src/main.cpp
)

target_compile_features(Project_2___Cogwork_Engineers PRIVATE cxx_std_17)
target_link_libraries(Project_2___Cogwork_Engineers PRIVATE SFML::Graphics)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Project_2___Cogwork_Engineers)
