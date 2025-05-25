#ifndef PCA9685_CONSTANTS_HPP
#define PCA9685_CONSTANTS_HPP


#define PCA9685_ADDRESS             0x00
#define PCA9685_RESET               0x00

// ERROR CODES
#define PCA9685_OK                  0x00
#define PCA9685_ERROR               0xFF
#define PCA9685_ERR_CHANNEL         0xFE
#define PCA9685_ERR_MODE            0xFD
#define PCA9685_ERR_I2C             0xFC

//  get/setFrequency()
#define PCA9685_MIN_FREQ              24
#define PCA9685_MAX_FREQ            1526


//  REGISTERS CONFIGURATION - check datasheet for details
#define PCA9685_MODE1               0x00
#define PCA9685_MODE2               0x01

//  Configuration bits MODE1 register
#define PCA9685_MODE1_RESTART       0x80  //  0 = disable      1 = enable
#define PCA9685_MODE1_EXTCLK        0x40  //  0 = internal     1 = external (datasheet)
#define PCA9685_MODE1_AUTOINCR      0x20  //  0 = disable      1 = enable
#define PCA9685_MODE1_SLEEP         0x10  //  0 = normal       1 = sleep
#define PCA9685_MODE1_SUB1          0x08  //  0 = disable      1 = enable
#define PCA9685_MODE1_SUB2          0x04  //  0 = disable      1 = enable
#define PCA9685_MODE1_SUB3          0x02  //  0 = disable      1 = enable
#define PCA9685_MODE1_ALLCALL       0x01  //  0 = disable      1 = enable
#define PCA9685_MODE1_NONE          0x00

//  Configuration bits MODE2 register
#define PCA9685_MODE2_INVERT        0x10  //  0 = normal       1 = inverted
#define PCA9685_MODE2_ACK           0x08  //  0 = on STOP      1 = on ACK
#define PCA9685_MODE2_TOTEMPOLE     0x04  //  0 = open drain   1 = totem-pole
#define PCA9685_MODE2_OUTNE         0x03  //  datasheet
#define PCA9685_MODE2_NONE          0x00

#define PCA9685_SUBADR(x)           (0x01 + (x))  //  x = 1..3
#define PCA9685_ALLCALLADR          0x05

// REGISTERS - CHANNELS
//  0x06 + 4*channel is base per channel
#define PCA9685_CHANNEL_0           0x06
#define PCA9685_CHANNEL(x)          (0x06 + ((x) * 4))  //  x = 0..15

//  REGISTERS - ALL_ON ALL_OFF
#define PCA9685_ALL_ON_L            0xFA
#define PCA9685_ALL_ON_H            0xFB
#define PCA9685_ALL_OFF_L           0xFC
#define PCA9685_ALL_OFF_H           0xFD   //  used for allOFF()

// REGISTERS - FREQUENCY
#define PCA9685_PRE_SCALER          0xFE

//  NOT IMPLEMENTED
//  WARNING: DO NOT USE THIS REGISTER (see datasheet)
#define PCA9685_TESTMODE            0xFF   //  do not be use. see datasheet.

#endif // PCA9685_CONSTANTS_HPP
