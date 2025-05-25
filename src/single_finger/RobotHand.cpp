#include "RobotHand.hpp"
#include <algorithm>

extern "C" void HAL_Delay(uint32_t ms);

RobotHand::RobotHand()
    : scl(hal::Port::B, 8)
    , sda(hal::Port::B, 9)
    , i2c(1, scl, sda)
    , pca9685Address(0x40)
    , resetPca9685Address(0x00)
    , pca9685(i2c, pca9685Address)
    , commandQueue()
    , isTransmitting(false)
    , initialized(false)
{}

void RobotHand::Initialize()
{
    ResetDevice();
}

void RobotHand::ResetDevice()
{
    static const uint8_t resetData[] = {0x06};
    isTransmitting = true;

    i2c.SendData(resetPca9685Address, infra::MakeConstByteRange(resetData), hal::Action::stop,
        [this](hal::Result, uint32_t) {
            isTransmitting = false;
            HAL_Delay(10);
            InitializePca9685();
            initialized = true;
            SendNextMessage();
        });
}

void RobotHand::InitializePca9685()
{
    static const uint8_t data1[] = { 0x20 };
    static const uint8_t data2[] = { 0x04 };
    static const uint8_t data3[] = { 0x10 };
    static const uint8_t data4[] = { 0x79 };

    QueueI2CMessage(0x00, infra::MakeConstByteRange(data1), 0, I2CPriority::HIGH);
    QueueI2CMessage(0x01, infra::MakeConstByteRange(data2), 0, I2CPriority::HIGH);
    QueueI2CMessage(0x00, infra::MakeConstByteRange(data3), 0, I2CPriority::HIGH);
    QueueI2CMessage(0xFE, infra::MakeConstByteRange(data4), 0, I2CPriority::HIGH);
    QueueI2CMessage(0x00, infra::MakeConstByteRange(data1), 10, I2CPriority::HIGH);
}

void RobotHand::QueueI2CMessage(uint8_t reg, infra::ConstByteRange data, uint32_t delayMs, I2CPriority priority)
{
    commandQueue.Push({reg, data, delayMs, priority});
    SortCommandQueue();
    if (!isTransmitting && initialized)
        SendNextMessage();
}

void RobotHand::SendNextMessage()
{
    if (commandQueue.Empty() || isTransmitting)
        return;

    isTransmitting = true;
    auto& command = commandQueue.ContiguousRange()[0];

    pca9685.WriteRegister(command.registerAddress, command.data,
        [this, delayMs = command.delayMs]() {
            HAL_Delay(delayMs);
            OnMessageComplete();
        });
}

void RobotHand::OnMessageComplete()
{
    commandQueue.Pop(1);
    isTransmitting = false;
    SendNextMessage();
}

uint16_t MapPercentageToPulse(uint8_t percentage, uint16_t minPulse = 205, uint16_t maxPulse = 410)
{
    if (percentage > 100)
        percentage = 100;
    return static_cast<uint16_t>(minPulse + ((maxPulse - minPulse) * percentage) / 100);
}

void RobotHand::MoveFinger(Finger finger, uint8_t percentageOpen, uint32_t delayMs)
{
    uint8_t registerAddress = static_cast<uint8_t>(finger);

    int fingerIndex;
    switch (finger)
    {
        case Finger::FINGER_1: fingerIndex = 0; break;
        case Finger::FINGER_2: fingerIndex = 1; break;
        case Finger::FINGER_3: fingerIndex = 2; break;
        case Finger::FINGER_4: fingerIndex = 3; break;
        case Finger::FINGER_5: fingerIndex = 4; break;
        default: return; // prevent out-of-bounds access
    }

    if (finger == Finger::FINGER_1)
        percentageOpen = 100 - percentageOpen;

    uint16_t pulse = MapPercentageToPulse(percentageOpen);

    MoveFingerData[fingerIndex][0] = 0x00;           // ON_L
    MoveFingerData[fingerIndex][1] = 0x00;           // ON_H
    MoveFingerData[fingerIndex][2] = pulse & 0xFF;   // OFF_L
    MoveFingerData[fingerIndex][3] = pulse >> 8;     // OFF_H

    QueueI2CMessage(registerAddress, infra::MakeConstByteRange(MoveFingerData[fingerIndex]), delayMs, I2CPriority::LOW);
}

void RobotHand::SortCommandQueue() {
    std::array<I2CCommand, 2048> tempArray;
    size_t queueSize = commandQueue.Size();
    
    for (size_t i = 0; i < queueSize; ++i) {
        tempArray[i] = commandQueue.ContiguousRange()[i];
    }
    
    std::sort(tempArray.begin(), tempArray.begin() + queueSize, [](const I2CCommand& a, const I2CCommand& b) {
        return a.priority < b.priority;
    });
    
    for (size_t i = 0; i < queueSize; ++i) {
        commandQueue.Pop(1);
        commandQueue.Push(tempArray[i]);
    }
}



