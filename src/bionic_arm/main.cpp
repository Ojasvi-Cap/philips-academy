#include "hal_st/instantiations/NucleoUi.hpp"
#include "hal_st/instantiations/StmEventInfrastructure.hpp"
#include "hal_st/stm32fxxx/DefaultClockNucleoF429ZI.hpp"
#include "services/util/DebouncedButton.hpp"
#include "infra/timer/Timer.hpp"
#include "RobotHand.hpp"
#include <array>

unsigned int hse_value = 24'000'000;

static main_::NUCLEO ui;

class FingerAutoCloserGroup
{
public:
    FingerAutoCloserGroup(RobotHand& robotHand)
        : robotHand(robotHand)
        , timer(0) {}

    void OpenAllAndCloseAfter(infra::Duration duration)
    {
        for (Finger finger : allFingers)
            robotHand.MoveFinger(finger, 100, 0); // Open

        timer.Start(duration, [this]() {
            for (Finger finger : allFingers)
                robotHand.MoveFinger(finger, 0, 0); // Close
        });
    }

private:
    RobotHand& robotHand;
    infra::TimerSingleShot timer;
    const std::array<Finger, 5> allFingers{
        Finger::FINGER_1, Finger::FINGER_2, Finger::FINGER_3,
        Finger::FINGER_4, Finger::FINGER_5
    };
};

int main()
{
    HAL_Init();
    ConfigureDefaultClockNucleoF429ZI();

    static main_::StmEventInfrastructure infra;
    static RobotHand robotHand;
    robotHand.Initialize();

    static FingerAutoCloserGroup autoCloser(robotHand);

    static services::DebouncedButton debouncedButton(
        ui.buttonOne,
        [] {
            autoCloser.OpenAllAndCloseAfter(infra::Duration(std::chrono::milliseconds(200)));
        },
        [] {}
    );

    infra.Run();
    __builtin_unreachable();
}
