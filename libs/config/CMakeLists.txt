cmake_minimum_required(VERSION 3.20)

set(TARGET_NAME_BASE config)

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

if (MSVC)
	# /W4 (Warning Level)
	target_compile_options(${TARGET_NAME} INTERFACE /W4)

	# /WX (Treat all warnings as errors)
	target_compile_options(${TARGET_NAME} INTERFACE /WX)

	# /GR- (Disable Run-Time Type Information)
	target_compile_options(${TARGET_NAME} INTERFACE /GR-)

	# /MP (Build with Multiple Processes)
	if (NOT CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
		target_compile_options(${TARGET_NAME} INTERFACE /MP)
	endif()

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	target_compile_options(${TARGET_NAME} INTERFACE -Wall -Wextra -Werror)

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	target_compile_options(${TARGET_NAME} INTERFACE -Wall -Wextra -Werror)

endif()

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	add_subdirectory(test)
endif()
