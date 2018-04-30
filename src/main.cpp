#include "mbed.h"
#include <string>
#include <cJSON.h>
#include <Flasher.h>
#include <SawTooth.h>
#include <Stepper.h>
#include <Servo.h>

// 12V speed set at 400 steps/second
// 488 Just right
// #define MOTOR_DISTANCE 482
#define MOTOR_DISTANCE 472
#define RAMP_STEPS 25

// RS485 commands set
#define CMD_CC_ID 0x10
#define CMD_CC_MOVE_1 0x21
#define CMD_CC_MOVE_2 0x22
#define CMD_CC_MOVE_3 0x23
#define CMD_CC_TRIGGER_1 0x31
#define CMD_CC_TRIGGER_2 0x32
#define CMD_CC_TRIGGER_3 0x33
#define CMD_CC_TRIGGER_4 0x34

#define ERR_CC_CMD_UNKNOWN 0xf0
#define ERR_CC_CMD_TOOSHORT 0xf1

// Global variables
int COMMAND_FLAG = 0, LIMIT_SWITCH1=0, LIMIT_SWITCH2=0, LIMIT_SWITCH3=0;
// ccles: number of periods to run
// NOTE:
// set speed = 330 for older model
// set speed = 450 for new model
//int move=0, trigger=0, speed = 330;
int move=0, trigger=0, speed=450;

Serial pc(USBTX, USBRX, 57600);
Serial rs485(p13, p14, 57600);
DigitalOut RST_EN(p15);

// Pin assigment
// p25: Servo
// p18: Sawtooth
// p5, p6, p7, p8: Stepper
// p11, p12: Reset
// p21, p22, p23, p24, p25: Limit Switch
// p26, p27, p28: LED Control

// Servo testing
Servo myServo(p25);

Ticker flipper;
Ticker flipper2;
Ticker ticker;
PwmOut led1(LED1);
DigitalOut led2(LED2);

Flasher led3(LED3);
Flasher led4(LED4, 2);

// Stepper motor control
// stepperA is at connector P3
// stepperB is at connector P4
stepper stepperA(p5, p6);
stepper stepperB(p7, p8);
DigitalOut resetA(p11);
DigitalOut resetB(p12);

// Limit switch checking
PwmOut buzzer(p21);
InterruptIn limitSwitch1(p22);
InterruptIn limitSwitch2(p24);
InterruptIn limitSwitch3(p25);
//InterruptIn limitSwitch4(p25);
string interruptIndicator = "";

// LED Control
DigitalOut highPowerLED1(p26);
DigitalOut highPowerLED2(p27);
DigitalOut highPowerLED3(p28);
DigitalOut highPowerLED4(p29);

// Local Helpers
bool isSubString(string str1, string str2) {
  return str1.find(str2) != std::string::npos;
}

void flip2() {
  led1 = !led1;
}

void flip() {
  led2 = !led2;
}

void disableStepper() {
  resetA = 0;
  resetB = 0;
  wait_ms(1);
}

void enableStepper() {
  resetA = 1;
  resetB = 1;
  wait_ms(1);
}

void moveForward(int speed) {
  //stepperA.step(MOTOR_DISTANCE, 1, speed, false);
  // for (int i=0; i < RAMP_STEPS; i++) {
  //   stepperB.step(static_cast<int>(MOTOR_DISTANCE/RAMP_STEPS/4), 1, static_cast<int>(speed*i/RAMP_STEPS), false);
  //   //stepperB.step(MOTOR_DISTANCE*1/4, 1, speed, true);
  // }
  // stepperB.step(MOTOR_DISTANCE/4, 1, speed, true);
  // stepperB.step(MOTOR_DISTANCE*3/4, 1, speed, false);
  stepperB.step(MOTOR_DISTANCE, 1, speed, false);
}

void moveBackward(int speed) {
  //stepperA.step(MOTOR_DISTANCE, 0, speed, false);
  // for (int i=0; i < RAMP_STEPS; i++) {
  //   stepperB.step(static_cast<int>(MOTOR_DISTANCE/RAMP_STEPS/4), 0, static_cast<int>(speed*i/RAMP_STEPS), false);
  //   //stepperB.step(MOTOR_DISTANCE*1/4, 1, speed, true);
  //   //stepperB.step(MOTOR_DISTANCE*3/4, 0, speed, false);
  // }
  // stepperB.step(MOTOR_DISTANCE/4, 0, speed, true);
  // stepperB.step(MOTOR_DISTANCE*3/4, 0, speed, false);
  stepperB.step(MOTOR_DISTANCE * 2.3, 0, speed, false);
}

void moveMotor(int pos, int speed) {
  enableStepper();
  switch (pos) {
    case 1:
      moveBackward(speed);
      break;
    case 2:
      moveForward(speed);
      break;
    case 3:
      moveForward(speed);
      break;
    default:
      break;
  }
}

void triggerLED(int led_number) {
  switch (led_number) {
    case 1:
      highPowerLED1 = 1;
      break;
    case 2:
      highPowerLED2 = 1;
      break;
    case 3:
      highPowerLED3 = 1;
      break;
    case 4:
      highPowerLED4 = 1;
      break;
    default:
      break;
  }

  wait(0.1f);

  highPowerLED1 = 0;
  highPowerLED2 = 0;
  highPowerLED3 = 0;
  highPowerLED4 = 0;
  return;
}

void sendFeedback(string paraName,int para) {
  printf("{ \"%s\": %d }\n", paraName.c_str(), para);
}

void sendRS485(string message) {
  RST_EN = 1;
  wait_ms(1);
  rs485.printf("{%s}\n", message.c_str());
  // NOTE: this delay is essiential for message to be fully transimitted
  // increate the delay time if message found being cut half-way
  wait_ms(4);
  RST_EN = 0;
}


void onPosition1() {
  //disableStepper();
  sendFeedback("position", 1);
  sendRS485("cc_POSITION_1");
  //wait_ms(50);
}

void onPosition2() {
  disableStepper();
  sendFeedback("position", 2);
  sendRS485("cc_POSITION_2");
  //wait_ms(50);
}

void onPosition3() {
  disableStepper();
  sendFeedback("position", 3);
  sendRS485("cc_POSITION_3");
  //wait_ms(50);
}


// void checkPinOld() {
//   // Don't disable Motor continously
//   // if (limitSwitch1 == 1 || limitSwitch2 == 1 || limitSwitch3 == 1) {
//   //   disableStepper();
//   // }
//
//   // Rising
//   if (limitSwitch1 == 1 && LIMIT_SWITCH1 == 0) {
//     LIMIT_SWITCH1 = 1;
//     onPosition1();
//   } else {
//     if (limitSwitch1 == 0 && LIMIT_SWITCH1 == 1) {
//       LIMIT_SWITCH1 = 0;
//     }
//   }
//
//   if (limitSwitch2 == 1 && LIMIT_SWITCH2 == 0) {
//     // Don't trigger on the way back to Position1
//     if (move !=1) {
//       LIMIT_SWITCH2 = 1;
//       //onPosition2();
//     }
//   } else {
//     if (limitSwitch2 == 0 && LIMIT_SWITCH2 == 1) {
//       LIMIT_SWITCH2 = 0;
//     }
//   }
//
//   if (limitSwitch3 == 1 && LIMIT_SWITCH3 == 0) {
//       LIMIT_SWITCH3 = 1;
//       //onPosition3();
//   } else {
//     if (limitSwitch3 == 0 && LIMIT_SWITCH3 == 1) {
//       LIMIT_SWITCH3 = 0;
//     }
//   }
// }

void checkPin() {
  // Falling
  if (limitSwitch1 == 0 && LIMIT_SWITCH1 == 0) {
    LIMIT_SWITCH1 = 1;
    onPosition1();
    disableStepper();
  } else {
    if (limitSwitch1 == 1 && LIMIT_SWITCH1 == 1) {
      LIMIT_SWITCH1 = 0;
    }
  }
}

// Read From VCP
void readPC() {
  // Disable the ISR during handling
  pc.attach(0);

  // Note: you need to actually read from the serial to clear the RX interrupt
  //char _buffer[128];
  string holder;
  cJSON *json;
  // parameters list
  // factor: scale of 3V
  // ccles: number of periods to run
  //int move=0, trigger=0;
  int _speed = speed;

  int errorStatus=0;

  char temp;
  while(temp != '\n') {
    temp = pc.getc();
    holder += temp;
  }
  if (holder.length() < 5) return;

  json = cJSON_Parse(holder.c_str());
  if (!json) {
    printf("Error before: [%s]\n", cJSON_GetErrorPtr());
  } else {
    // move = cJSON_GetObjectItem(json, "move")->valueint;
    // trigger = cJSON_GetObjectItem(json, "trigger")->valueint;
    _speed = cJSON_GetObjectItem(json, "speed")->valueint;
    cJSON_Delete(json);

    if (_speed <=100 || _speed >= 500) {
      printf("Motor speed must be within [100 - 500]\n");
    } else {
      printf("Motor speed set to [%d]\n", _speed);
      speed = _speed;
    }
  }

  // Set COMMAND_FLAG to true, ready to handle inside main

  // Move Stepper Motor
  // if (move != 0) {
  //   COMMAND_FLAG = 1;
  // }
  //
  // if (trigger !=0) {
  //
  // }

  // Restore ISR when everything is done:
  pc.attach(&readPC);
}

void readRS485() {
  // Disable the ISR during handling
  rs485.attach(0);
  // Note: you need to actually read from the serial to clear the RX interrupt
  //char _buffer[128];
  string holder;
  cJSON *json;
  // parameters list
  // factor: scale of 3V
  // ccles: number of periods to run
  //int move=0, trigger=0;

  int errorStatus=0;
  int command = 0;

  char temp;
  while(temp != '\n') {
    temp = rs485.getc();
    holder += temp;
  }
  // NOTE: cannot directly return from a ISR
  if (holder.length() < 5) command = ERR_CC_CMD_TOOSHORT;

  if (isSubString(holder, "cc_ID")) command = CMD_CC_ID;
  if (isSubString(holder, "cc_MOVE_1")) command = CMD_CC_MOVE_1;
  if (isSubString(holder, "cc_MOVE_2")) command = CMD_CC_MOVE_2;
  if (isSubString(holder, "cc_MOVE_3")) command = CMD_CC_MOVE_3;
  if (isSubString(holder, "cc_TRIGGER_1")) command = CMD_CC_TRIGGER_1;
  if (isSubString(holder, "cc_TRIGGER_2")) command = CMD_CC_TRIGGER_2;
  if (isSubString(holder, "cc_TRIGGER_3")) command = CMD_CC_TRIGGER_3;
  if (isSubString(holder, "cc_TRIGGER_4")) command = CMD_CC_TRIGGER_4;

  // Parse RS485 commands
  switch (command) {
    case CMD_CC_ID:
      sendRS485("cc_ACK");
      break;

    case CMD_CC_MOVE_1:
      move = 1;
      COMMAND_FLAG = 1;
      break;

    case CMD_CC_MOVE_2:
      move = 2;
      COMMAND_FLAG = 1;
      break;

    case CMD_CC_MOVE_3:
      move = 3;
      COMMAND_FLAG = 1;
      break;

    case CMD_CC_TRIGGER_1:
      trigger = 1;
      COMMAND_FLAG = 1;
      break;

    case CMD_CC_TRIGGER_2:
      trigger = 2;
      COMMAND_FLAG = 1;
      break;

    case CMD_CC_TRIGGER_3:
      trigger = 3;
      COMMAND_FLAG = 1;
      break;

    case CMD_CC_TRIGGER_4:
      trigger = 4;
      COMMAND_FLAG = 1;
      break;

    default:
      //sendRS485("cc_UNKNOWN_CMD");
      break;
  }

  // Restore ISR when everything is done:
  rs485.attach(&readRS485);
}

int main() {
  led2 = 1;
  resetA = 1;
  resetB = 1;

  RST_EN = 0;

  highPowerLED1 = 0;
  highPowerLED2 = 0;
  highPowerLED3 = 0;
  highPowerLED4 = 0;

  led3.flash(1);
  led4.flash(3);

  flipper.attach(&flip, 1); // the address of the function to be attached (flip) and the interval (2 seconds)
  ticker.attach(&checkPin, 0.02);

  printf("version: [%d]\n", 121);
  sendRS485("cc_init");

  pc.attach(&readPC);
  rs485.attach(&readRS485);

  while(1) {
    if (COMMAND_FLAG == 1) {
      //pc.printf("To Move Motor %d", move);
      COMMAND_FLAG = 0;
      moveMotor(move, speed);
      // TODO: temp put pos2 feedback here
      if (move ==2) {
        onPosition2();
      }
      if (move ==3) {
        onPosition3();
      }
      triggerLED(trigger);
      move = 0;
      trigger = 0;
    }
    wait(0.1f);
  }
}
