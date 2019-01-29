cmake_minimum_required(VERSION 3.6)
project(Raytracing)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)

set(source_files
        src/main.cpp
)

# Remove the cmd window for release builds
set(EXECUTABLE_WIN32 "")
if (WIN32 AND "${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    set(EXECUTABLE_WIN32 "WIN32")
endif ()

find_package(Boost COMPONENTS system filesystem REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(Raytracing ${EXECUTABLE_WIN32} ${source_files})
target_link_libraries(Raytracing ${OpenCV_LIBS})
target_link_libraries(Raytracing yaml-cpp)
target_link_libraries(Raytracing ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY})