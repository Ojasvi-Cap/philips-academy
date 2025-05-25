#pragma once
#include <cstdint>

enum class Finger : uint8_t
{
    FINGER_1,
    FINGER_2,
    FINGER_3,
    FINGER_4,
    FINGER_5
};

// This is a minimal testable version — no STM32 dependency
class MockRobotHand
{
public:
    bool initialized = false;
    std::vector<std::pair<Finger, std::pair<uint8_t, uint8_t>>> calls;

    void Initialize()
    {
        initialized = true;
    }

    void MoveFinger(Finger finger, uint8_t angle, uint8_t grip)
    {
        if (initialized)
            calls.emplace_back(finger, std::make_pair(angle, grip));
    }
};
