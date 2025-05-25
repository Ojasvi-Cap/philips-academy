#include "gtest/gtest.h"
#include "MockRobotHand.hpp"

TEST(RobotHandTest, CanMoveFingerAfterInit)
{
    MockRobotHand hand;
    hand.Initialize();
    hand.MoveFinger(Finger::FINGER_1, 0, 0);

    ASSERT_EQ(hand.calls.size(), 1);
    EXPECT_EQ(hand.calls[0].first, Finger::FINGER_1);
    EXPECT_EQ(hand.calls[0].second.first, 0); // angle
    EXPECT_EQ(hand.calls[0].second.second, 0); // grip
}


// #include "RobotHand.hpp"
// #include "gmock/gmock.h"
// #include "gtest/gtest.h"
// #include "hal/interfaces/I2c.hpp"
// #include "hal/interfaces/I2cRegisterAccess.hpp"
// #include "infra/util/MemoryRange.hpp"

// using namespace testing;

// class I2cAccessMock : public hal::I2cMasterRegisterAccessByte
// {
// public:
//     I2cAccessMock()
//         : hal::I2cMasterRegisterAccessByte(i2cMock, hal::I2cAddress{0x40}) {}

//     MOCK_METHOD(void, WriteRegister, (
//         uint8_t reg,
//         infra::ConstByteRange data,
//         const infra::Function<void()>& onDone
//     ), (override));

//     StrictMock<hal::MockI2cMaster> i2cMock;
// };

// // Subclass RobotHand just for testing
// class RobotHandTestable : public RobotHand
// {
// public:
//     RobotHandTestable()
//     {
//         // Overwrite internal PCA9685 with mock
//         pcaMock = std::make_unique<I2cAccessMock>();
//         this->pca9685 = *pcaMock;
//     }

//     std::unique_ptr<I2cAccessMock> pcaMock;
// };

// class RobotHandTest : public Test
// {
// protected:
//     void SetUp() override
//     {
//         hand = std::make_unique<RobotHandTestable>();
//         hand->initialized = true;
//     }

//     std::unique_ptr<RobotHandTestable> hand;
// };

// TEST_F(RobotHandTest, MoveFinger1SendsCorrectRegisterData)
// {
//     uint8_t expectedReg = 0x06;
//     uint8_t expectedPWM[] = {0x00, 0x00, 0xA8, 0x01};

//     EXPECT_CALL(*hand->pcaMock, WriteRegister(expectedReg,
//         Truly([&](infra::ConstByteRange data) {
//             return std::equal(data.begin(), data.end(), std::begin(expectedPWM));
//         }),
//         _
//     ));

//     hand->MoveFinger(Finger::FINGER_1, 0, 0); // 0% -> 100% open
// }
