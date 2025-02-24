cmake_minimum_required(VERSION 3.25)
project(PhantasmEngine VERSION 1.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(FATAL "32-bit builds are not supported.")
endif()

option(PHENGINE_STATIC "Build static library instead of shared" OFF)

find_package(SDL3 3.2.4 REQUIRED)
if(NOT DEFINED BROTLI_INCLUDE_DIRS OR NOT DEFINED BROTLI_LIBRARIES)
    message(FATAL_ERROR "BROTLI_INCLUDE_DIRS and BROTLI_LIBRARIES need to be defined")
endif()

set(PHENGINE_SRC_FILES
    src/ContentManager.cpp
    src/Game.cpp
    src/GameUpdate.cpp
    src/GraphicsDevice.cpp
    src/Monitor.cpp
    src/TaskExecutor.cpp
    src/TextureAtlas.cpp
    src/Window.cpp

    src/Graphics/GL.cpp
    src/Graphics/SpriteFont.cpp

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
        message(FATAL_ERROR "not done yet")
    else()
        add_library(PhEngine SHARED ${PHENGINE_SRC_FILES} ${PHENGINE_WIN64_SRC_FILES})
        target_include_directories(PhEngine PUBLIC include ${BROTLI_INCLUDE_DIRS})
        target_compile_definitions(PhEngine PUBLIC PHENGINE_SHARED UNICODE _UNICODE)
        target_compile_definitions(PhEngine PRIVATE PHENGINE_BUILDING_DLL)
        target_link_libraries(PhEngine ${BROTLI_LIBRARIES} SDL3::SDL3)
    endif()
else()
    if(PHENGINE_STATIC)
	message(FATAL_ERROR "not done yet")
    else()
	add_library(PhEngine SHARED ${PHENGINE_SRC_FILES})
	target_include_directories(PhEngine PUBLIC include ${BROTLI_INCLUDE_DIRS})
	target_compile_definitions(PhEngine PRIVATE PHENGINE_BUILDING_DLL)
	target_link_libraries(PhEngine ${BROTLI_LIBRARIES} SDL3::SDL3)
    endif()
endif()
