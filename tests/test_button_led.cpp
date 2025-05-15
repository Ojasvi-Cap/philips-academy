#include "gtest/gtest.h"
#include "ButtonLedLogic.hpp"

class ButtonLedLogicTest : public ::testing::Test {
protected:
    bool ledState = false;

    ButtonLedLogic logic{
        [&]() { ledState = true; },
        [&]() { ledState = false; }
    };
};

TEST_F(ButtonLedLogicTest, TurnsLedOnWhenPressed) {
    logic.HandlePress();
    EXPECT_TRUE(ledState);
}

TEST_F(ButtonLedLogicTest, TurnsLedOffWhenReleased) {
    logic.HandlePress();   // turn it on first
    logic.HandleRelease();
    EXPECT_FALSE(ledState);
}

