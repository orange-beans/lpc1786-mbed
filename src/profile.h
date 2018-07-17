#ifndef __PROFILE_H
#define __PROFILE_H

//****** Note ******//
// this header file is used to define 
// 1. Hardware profile settings;
// 2. user defined varables;
// 3. commands used for this hardware;

//****** Define Hardware Profile Settings ******//
#define MOTOR_DISTANCE 10
#define RAMP_STEPS 25

//****** Define User Defined Varables ******//
typedef struct {
  int intValue;
  double floatValue;
} token_t;

typedef struct {
  bool isChanged;
  unsigned int pwmPeriod;
  double pwmOuts[4];
  unsigned int dOutsByte;
  unsigned char dIns[8];
  float aOutValue;
  unsigned int motorSpeed[2];
  int motorDistance[2];
} system_setting_t;

//****** Define Commands ******//
#define CC_ID 0x10

#define CC_ON_DOUT   0x20
#define CC_OFF_DOUT  0x21
#define CC_SET_DOUTS 0x22

#define CC_READ_DIN  0x25
#define CC_READ_DINS 0x26

#define CC_PWM_PERIOD   0x30
#define CC_PWM0         0x31
#define CC_PWM1         0x32
#define CC_PWM2         0x33
#define CC_PWM3         0x34

#define CC_READ_AIN  0x40
#define CC_SET_AOUT  0x41

#define CC_MOTOR0_CW    0x60
#define CC_MOTOR0_CCW   0x61
#define CC_MOTOR0_SPEED 0x62
#define CC_MOTOR1_CW    0x65
#define CC_MOTOR1_CCW   0x66
#define CC_MOTOR1_SPEED 0x67

// #define CC_ROTATE_CW    0x60
// #define CC_ROTATE_CCW   0x61
// #define CC_HOME_MOTOR   0x62
// #define CC_SET_SPEED    0x63
// #define CC_SHAKE_MOTOR  0x64

#define CC_ON_ULTRA  0x50
#define CC_OFF_ULTRA 0x51

#define CC_ON_PUMP   0x60
#define CC_OFF_PUMP  0x61

#define ERR_CC_UNKNOWN 0xf0
#define ERR_CC_TOOSHORT 0xf1

// an I2C sub-class that provides a constructed default
class I2CPreInit : public I2C
{
  public:
    I2CPreInit(PinName sda, PinName scl) : I2C(sda, scl)
    {
      frequency(400000);
      start();
    };
};

#endif /* __PROFILE_H */