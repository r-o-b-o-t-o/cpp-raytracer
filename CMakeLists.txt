cmake_minimum_required(VERSION 3.6)
project(Raytracing)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)
find_package(Boost COMPONENTS system filesystem REQUIRED)

set(source_files
        src/main.cpp
        src/maths/Point.cpp
        src/maths/HPoint.cpp
        src/maths/Vector.cpp
        src/maths/HVector.cpp
        src/maths/Ray.cpp
        src/maths/Matrix.cpp
        src/scene/Entity.cpp
        src/scene/Object.cpp
        src/scene/Sphere.cpp
        src/scene/Plane.cpp
        src/scene/Square.cpp
        src/scene/Cube.cpp
        src/scene/Camera.cpp
        src/scene/Light.cpp
        src/scene/Color.cpp
        src/scene/Scene.cpp
        src/scene/Material.cpp
        src/scene/MaterialProvider.cpp
)

if (NOT YamlCpp_LIBS)
    set(YamlCpp_LIBS "yaml-cpp")
endif ()

# Remove the cmd window for release builds
set(EXECUTABLE_WIN32 "")
if (WIN32 AND "${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    set(EXECUTABLE_WIN32 "WIN32")
endif ()

include_directories("include")
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${YamlCpp_INCLUDE_DIRS})
add_executable(Raytracing ${EXECUTABLE_WIN32} ${source_files})
target_link_libraries(Raytracing ${OpenCV_LIBS})
target_link_libraries(Raytracing ${YamlCpp_LIBS})
target_link_libraries(Raytracing ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY})
