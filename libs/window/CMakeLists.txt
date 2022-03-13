cmake_minimum_required(VERSION 3.20)

set(TARGET_NAME_BASE window)

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

find_package(X11)
if (X11_FOUND)
	target_link_libraries(${TARGET_NAME} INTERFACE X11::X11)
endif()

add_subdirectory(samples)
