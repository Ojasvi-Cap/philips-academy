# add_executable(test_button_led
#     test_button_led.cpp
#     ${CMAKE_SOURCE_DIR}/src/button/ButtonLedLogic.cpp
# )

# # Add include directories
# target_include_directories(test_button_led PRIVATE
#     ${CMAKE_SOURCE_DIR}/src/button
# )

# # Link with libraries (GoogleTest and amp utils)
# target_link_libraries(test_button_led PRIVATE
#     gtest
#     gtest_main
#     infra.util
# )

# Register the test with CTest
# add_test(NAME ButtonLedLogicTest COMMAND test_button_led)

#testing robot hand
# -------------------------------
# Test: ButtonLedLogic
# -------------------------------
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


# -------------------------------
# Test: RobotHand
# -------------------------------
add_executable(test_robot_hand
    test_robot_hand.cpp
    MockRobotHand.hpp
)
target_link_libraries(test_robot_hand
    gtest_main
)
add_test(NAME RobotHandTest COMMAND test_robot_hand)

