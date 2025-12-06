cmake_minimum_required(VERSION 3.30)
project(PhantasmEngine VERSION 1.0.0 LANGUAGES CXX)

if(NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(FATAL_ERROR "32-bit builds are not supported.")
endif()

option(PHENGINE_STATIC "Build static library instead of shared" OFF)
option(PHENGINE_DEBUG "Enable debugging" OFF)
option(PHENGINE_VENDORED_SDL "Use vendored SDL" OFF)

if(PHENGINE_VENDORED_SDL)
    set(SDL_STATIC ON)
    set(SDL_SHARED OFF)
    set(SDL_STATIC_PIC ON)
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
    add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)
else()
    find_package(SDL3 3.2 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-static)
endif()

if(NOT DEFINED BROTLI_INCLUDE_DIRS OR NOT DEFINED BROTLI_LIBRARIES)
    message(FATAL_ERROR "BROTLI_INCLUDE_DIRS and BROTLI_LIBRARIES need to be defined")
endif()

# if(CMAKE_BUILD_TYPE STREQUAL "Debug")
#     set(PHENGINE_DEBUG ON)
#     message(STATUS "Debug version of Phantasm Engine 2D selected")
# endif()

set(PHENGINE_SRC_FILES
    src/ContentManager.cpp
    src/Exception.cpp
    src/Game.cpp
    src/GameUpdate.cpp
    src/GraphicsDevice.cpp
    src/Monitor.cpp
    src/TaskExecutor.cpp
    src/TextureAtlas.cpp
    src/Window.cpp

    src/Graphics/BatchRenderer.cpp
    src/Graphics/Shader.cpp
    src/Graphics/SpriteFont.cpp
)

if(PHENGINE_DEBUG)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
    set(PHENGINE_OPT_FILES src/GL_Debug.cpp)
else()
    set(PHENGINE_OPT_FILES src/GL.cpp)
endif()

if(WIN32)
    if(PHENGINE_STATIC)
        message(FATAL_ERROR "not done yet")
    else()
        add_library(PhEngine SHARED ${PHENGINE_SRC_FILES} ${PHENGINE_OPT_FILES})
        target_compile_features(PhEngine PUBLIC cxx_std_20)
        target_include_directories(PhEngine PUBLIC include ${BROTLI_INCLUDE_DIRS})
        target_compile_definitions(PhEngine PUBLIC PHENGINE_SHARED UNICODE _UNICODE)
        target_compile_definitions(PhEngine PUBLIC PHENGINE_BUILDING_DLL)
        if(PHENGINE_DEBUG)
            target_compile_definitions(PhEngine PUBLIC PHENGINE_DEBUG)
        endif()
        target_link_libraries(PhEngine ${BROTLI_LIBRARIES} SDL3::SDL3-static)
    endif()
else()
    if(PHENGINE_STATIC)
	    message(FATAL_ERROR "not done yet")
    else()
        add_library(PhEngine SHARED ${PHENGINE_SRC_FILES} ${PHENGINE_OPT_FILES})
        target_compile_features(PhEngine PUBLIC cxx_std_20)
        target_include_directories(PhEngine PUBLIC include ${BROTLI_INCLUDE_DIRS})
        target_compile_definitions(PhEngine PUBLIC PHENGINE_BUILDING_DLL)
        if(PHENGINE_DEBUG)
            target_compile_definitions(PhEngine PUBLIC PHENGINE_DEBUG)
        endif()
        target_link_libraries(PhEngine ${BROTLI_LIBRARIES} SDL3::SDL3-static)
    endif()
endif()
