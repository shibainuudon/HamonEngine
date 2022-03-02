set(TARGET_NAME "sample_window_window")

add_executable(${TARGET_NAME} sample_window_window_main.cpp)
set_target_properties(${TARGET_NAME} PROPERTIES FOLDER "samples")
target_link_libraries(${TARGET_NAME} PRIVATE Hamon::window)
