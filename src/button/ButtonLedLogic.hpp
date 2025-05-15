#pragma once

#include "infra/util/Function.hpp"

class ButtonLedLogic
{
public:
    ButtonLedLogic(infra::Function<void()> onPressed, infra::Function<void()> onReleased);

    void HandlePress();
    void HandleRelease();

private:
    infra::Function<void()> onPressed;
    infra::Function<void()> onReleased;
};
