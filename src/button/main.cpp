
#include "hal_st/instantiations/NucleoUi.hpp"
#include "hal_st/instantiations/StmEventInfrastructure.hpp"
#include "services/util/DebouncedButton.hpp"
#include "ButtonLedLogic.hpp"

unsigned int hse_value = 24'000'000;

static main_::NUCLEO ui;

int main()
{
    HAL_Init();

    static main_::StmEventInfrastructure eventInfrastructure;

    static ButtonLedLogic logic(
        [&]() { ui.ledBlue.Set(true); },   // Pressed
        [&]() { ui.ledBlue.Set(false); }   // Released
    );

    static services::DebouncedButton debouncedButton(
        ui.buttonOne,
        [&]() { logic.HandlePress(); },
        [&]() { logic.HandleRelease(); }
    );

    eventInfrastructure.Run();
    __builtin_unreachable();
}
