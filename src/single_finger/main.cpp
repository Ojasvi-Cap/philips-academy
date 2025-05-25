#include "hal_st/instantiations/NucleoUi.hpp"
#include "hal_st/instantiations/StmEventInfrastructure.hpp"
#include "hal_st/stm32fxxx/DefaultClockNucleoF429ZI.hpp"
#include "services/util/DebouncedButton.hpp"
#include "infra/timer/Timer.hpp"
#include "RobotHand.hpp"

unsigned int hse_value = 24'000'000;

static main_::NUCLEO ui;

class FingerAutoCloser
{
public:
    FingerAutoCloser(RobotHand& robotHand, Finger finger)
        : robotHand(robotHand)
        , finger(finger)
        , timer(0) // 0 = system default timer service
    {}

    void OpenAndCloseAfter(infra::Duration duration)
    {
        robotHand.MoveFinger(finger, 100, 0); // Open
        timer.Start(duration, [this]() {
            robotHand.MoveFinger(finger, 0, 0); // Close
        });
    }

private:
    RobotHand& robotHand;
    Finger finger;
    infra::TimerSingleShot timer;
};

int main()
{
    HAL_Init();
    ConfigureDefaultClockNucleoF429ZI();

    static main_::StmEventInfrastructure infra;
    static RobotHand robotHand;
    robotHand.Initialize();

    static FingerAutoCloser autoCloser(robotHand, Finger::FINGER_1);

    static services::DebouncedButton debouncedButton(
        ui.buttonOne,
        // Press
        [] {
            autoCloser.OpenAndCloseAfter(infra::Duration(std::chrono::milliseconds(500)));

        },
        // Release
        [] {}
    );

    infra.Run();
    __builtin_unreachable();
}
