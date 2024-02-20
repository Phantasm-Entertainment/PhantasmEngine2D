cmake_minimum_required(VERSION 3.25)
project(PhantasmEngine VERSION 1.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(FATAL "32-bit builds are not supported.")
endif()

option(PHENGINE_STATIC "Build static library instead of shared" OFF)

find_package(GLFW3 3.3.9 REQUIRED)

set(PHENGINE_SRC_FILES
    src/Game.cpp
    src/GameUpdate.cpp
    src/TaskExecutor.cpp

    src/Math/Calculator.cpp
    src/Math/Matrix4.cpp
    src/Math/Rectangle.cpp
    src/Math/Vector2.cpp
    src/Math/Vector3.cpp
    src/Math/Vector4.cpp
)

set(PHENGINE_WIN64_SRC_FILES

)

if(WIN32)
    if(PHENGINE_STATIC)
        message(FATAL "not done yet")
    else()
        add_library(PhEngine SHARED ${PHENGINE_SRC_FILES} ${PHENGINE_WIN64_SRC_FILES})
        target_include_directories(PhEngine PUBLIC include ${GLFW_INCLUDE_DIRS})
        target_compile_definitions(PhEngine PUBLIC PHENGINE_SHARED UNICODE _UNICODE)
        target_compile_definitions(PhEngine PRIVATE PHENGINE_BUILDING_DLL)
        target_link_libraries(PhEngine ${GLFW_LIBRARIES})
    endif()
else()
    message(FATAL "not done yet")
endif()