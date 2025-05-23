cmake_minimum_required(VERSION 3.24)

file(GLOB SOURCES "*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_options(${PROJECT_NAME} PRIVATE -g -O0)

target_compile_definitions(${PROJECT_NAME} PUBLIC
    NUCLEO=Nucleo144Ui
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    services.util
    hal_st.instantiations
)

emil_build_for(${PROJECT_NAME} TARGET_MCU_VENDOR st PREREQUISITE_BOOL HALST_BUILD_EXAMPLES)
halst_target_default_linker_scripts(${PROJECT_NAME})
halst_target_default_init(${PROJECT_NAME})
emil_generate_artifacts(TARGET ${PROJECT_NAME} LST MAP BIN HEX)
