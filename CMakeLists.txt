cmake_minimum_required(VERSION 3.6)
project(Raytracing)

set(CMAKE_CXX_STANDARD 14)

include(CMakeLists.local.txt OPTIONAL)

find_package(OpenCV REQUIRED)
find_package(Boost COMPONENTS system filesystem REQUIRED)
find_package(Threads)
find_package(SFML 2.5 COMPONENTS graphics window system)
if (!WIN32)
    find_package(glfw3 REQUIRED)
    find_package(OpenGL REQUIRED)
    find_package(GLEW REQUIRED)
endif()

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

        src/imgui/imgui.cpp
        src/imgui/imgui_draw.cpp
        src/imgui/imgui_widgets.cpp
        src/imgui/imgui_demo.cpp
        src/imgui/imgui-SFML.cpp
)

if (NOT YamlCpp_LIBS)
    set(YamlCpp_LIBS "yaml-cpp")
endif ()

# Remove the cmd window for release builds
set(EXECUTABLE_WIN32 "")
if (WIN32 AND "${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    set(EXECUTABLE_WIN32 "WIN32")
endif ()

add_executable(Raytracing ${EXECUTABLE_WIN32} ${source_files})

include_directories("include")
include_directories("include/imgui")
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${YamlCpp_INCLUDE_DIRS})
if (!WIN32)
    include_directories(${GLFW_INCLUDE_DIRS})
    include_directories(${OPENGL_INCLUDE_DIRS})
    include_directories(${GLEW_INCLUDE_DIRS})
    link_libraries(${GLFW_LIBRARY_DIRS})
endif()
target_link_libraries(Raytracing ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(Raytracing ${OpenCV_LIBS})
target_link_libraries(Raytracing ${YamlCpp_LIBS})
target_link_libraries(Raytracing ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY})
target_link_libraries(Raytracing sfml-graphics sfml-window sfml-system)

if (APPLE)
    find_library(COCOA_LIBRARY Cocoa)
    find_library(OpenGL_LIBRARY OpenGL)
    find_library(IOKIT_LIBRARY IOKit)
    find_library(COREVIDEO_LIBRARY CoreVideo)
    SET(EXTRA_LIBS ${COCOA_LIBRARY} ${OpenGL_LIBRARY} ${IOKIT_LIBRARY} ${COREVIDEO_LIBRARY})
endif (APPLE)

if (WIN32)
    target_link_libraries(Raytracing opengl32)
else ()
    target_link_libraries(
        Raytracing
        glfw
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${EXTRA_LIBS}
    )
endif ()
