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

    src/Graphics/BatchRenderer.cpp
    src/Graphics/GL.cpp
    src/Graphics/Shader.cpp
    src/Graphics/SpriteFont.cpp
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif()

if(WIN32)
    if(PHENGINE_STATIC)
        message(FATAL_ERROR "not done yet")
    else()
        add_library(PhEngine SHARED ${PHENGINE_SRC_FILES} ${PHENGINE_WIN64_SRC_FILES})
        target_include_directories(PhEngine PUBLIC include ${BROTLI_INCLUDE_DIRS})
        target_compile_definitions(PhEngine PUBLIC PHENGINE_SHARED UNICODE _UNICODE)
        target_compile_definitions(PhEngine PRIVATE PHENGINE_BUILDING_DLL)
        if(CMAKE_BUILD_TYPE STREQUAL "Debug")
            target_compile_definitions(PhEngine PRIVATE PHENGINE_DEBUG)
            target_compile_options(PhEngine PRIVATE /fsanitize=address)
        endif()
        target_link_libraries(PhEngine ${BROTLI_LIBRARIES} SDL3::SDL3)
    endif()
else()
    if(PHENGINE_STATIC)
	message(FATAL_ERROR "not done yet")
    else()
    add_compile_options(-fsanitize=undefined -fsanitize=address)
	add_library(PhEngine SHARED ${PHENGINE_SRC_FILES})
	target_include_directories(PhEngine PUBLIC include ${BROTLI_INCLUDE_DIRS})
	target_compile_definitions(PhEngine PRIVATE PHENGINE_BUILDING_DLL)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_definitions(PhEngine PRIVATE PHENGINE_DEBUG)
        target_compile_options(PhEngine PRIVATE -fsanitize=undefined -fsanitize=address)
    endif()
	target_link_libraries(PhEngine ${BROTLI_LIBRARIES} SDL3::SDL3)
    endif()
endif()
