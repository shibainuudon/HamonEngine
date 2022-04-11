cmake_minimum_required(VERSION 3.20)

set(TARGET_NAME_BASE render)

set(TARGET_NAME hamon_${TARGET_NAME_BASE})
set(TARGET_ALIAS_NAME Hamon::${TARGET_NAME_BASE})

if (TARGET ${TARGET_NAME})
	RETURN()
endif()

project(${TARGET_NAME} LANGUAGES C CXX)

add_library(${TARGET_NAME} INTERFACE)
add_library(${TARGET_ALIAS_NAME} ALIAS ${TARGET_NAME})

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Include Directories
target_include_directories(${TARGET_NAME} INTERFACE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(${TARGET_NAME} INTERFACE ${PROJECT_SOURCE_DIR}/../../externals)

# Compile Options
if (MSVC)
	target_compile_options(${TARGET_NAME} INTERFACE /W4)
	target_compile_options(${TARGET_NAME} INTERFACE /WX)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	target_compile_options(${TARGET_NAME} INTERFACE -Wall -Wextra -Werror)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	target_compile_options(${TARGET_NAME} INTERFACE -Wall -Wextra -Werror)
endif()

# 依存ライブラリ
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../window ${CMAKE_CURRENT_BINARY_DIR}/window)
target_link_libraries(${TARGET_NAME} INTERFACE Hamon::window)

# D3D11, D3D12
if (WIN32)
	target_compile_definitions(${TARGET_NAME} INTERFACE HAMON_HAS_D3D11)
	target_compile_definitions(${TARGET_NAME} INTERFACE HAMON_HAS_D3D12)
endif()

# OpenGL
find_package(OpenGL)
if (OPENGL_FOUND)
	target_link_libraries(${TARGET_NAME} INTERFACE OpenGL::GL)
	target_compile_definitions(${TARGET_NAME} INTERFACE HAMON_HAS_OPEN_GL)
endif()

# Vulkan
find_package(Vulkan)
if (Vulkan_FOUND)
	target_link_libraries(${TARGET_NAME} INTERFACE Vulkan::Vulkan)
	target_compile_definitions(${TARGET_NAME} INTERFACE HAMON_HAS_VULKAN)
endif()

# glslang
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../externals/glslang ${CMAKE_CURRENT_BINARY_DIR}/externals/glslang)
target_link_libraries(${TARGET_NAME} INTERFACE glslang SPIRV)

# SPIRV-Cross
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../externals/SPIRV-Cross ${CMAKE_CURRENT_BINARY_DIR}/externals/SPIRV-Cross)
target_link_libraries(${TARGET_NAME} INTERFACE spirv-cross-glsl spirv-cross-hlsl)

# samples
add_subdirectory(samples)
