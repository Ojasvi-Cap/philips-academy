add_executable(test_button_led
    test_button_led.cpp
    ${CMAKE_SOURCE_DIR}/src/button/ButtonLedLogic.cpp
)

target_include_directories(test_button_led PRIVATE
    ${CMAKE_SOURCE_DIR}/src/button
)

target_link_libraries(test_button_led PRIVATE
    gtest
    gtest_main
    infra.util
)

add_test(NAME ButtonLedLogicTest COMMAND test_button_led)
