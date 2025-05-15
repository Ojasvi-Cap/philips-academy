#include "ButtonLedLogic.hpp"

ButtonLedLogic::ButtonLedLogic(infra::Function<void()> onPressed, infra::Function<void()> onReleased)
    : onPressed(std::move(onPressed))
    , onReleased(std::move(onReleased))
{}

void ButtonLedLogic::HandlePress()
{
    onPressed();
}

void ButtonLedLogic::HandleRelease()
{
    onReleased();
}
