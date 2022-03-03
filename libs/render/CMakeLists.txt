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

target_include_directories(${TARGET_NAME} INTERFACE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(${TARGET_NAME} INTERFACE ${PROJECT_SOURCE_DIR}/../../externals)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../window ${CMAKE_CURRENT_BINARY_DIR}/window)
target_link_libraries(${TARGET_NAME} INTERFACE Hamon::window)

find_package(OpenGL)
if (OPENGL_FOUND)
	target_link_libraries(${TARGET_NAME} INTERFACE OpenGL::GL)
endif()
add_subdirectory(samples)
