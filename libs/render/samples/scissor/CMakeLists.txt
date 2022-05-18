set(TARGET_NAME "sample_render_scissor")

add_executable(${TARGET_NAME} sample_render_scissor_main.cpp)
set_target_properties(${TARGET_NAME} PROPERTIES FOLDER "samples")
target_link_libraries(${TARGET_NAME} PRIVATE Hamon::render)
