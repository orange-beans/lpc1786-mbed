#include "mbed.h"
#include <string>
#include <cJSON.h>
#include <Flasher.h>
#include <SawTooth.h>
#include <Stepper.h>
#include <Servo.h>
Serial pc(USBTX, USBRX, 115200);

#define MOTOR_DISTANCE 5000

// Global variables
int COMMAND_FLAG = 0;
// ccles: number of periods to run
int move=0, trigger=0, speed = 1600;

// Pin assigment
// p25: Servo
// p18: Sawtooth
// p5, p6, p7, p8: Stepper
// p11, p12: Reset
// p21, p22, p23, p24, p25: Limit Switch
// p26, p27, p28: LED Control

// Servo testing
Servo myServo(p25);

// DAC pin18
//AnalogOut aout(p18);

Ticker flipper;
Ticker flipper2;
PwmOut led1(LED1);
//DigitalOut led1(LED1);
DigitalOut led2(LED2);
//DigitalOut led3(LED3);
//DigitalOut led4(LED4);

SawTooth sawTooth(p18, 0.5);
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


void flip2() {
  led1 = !led1;
}

void flip() {
  led2 = !led2;
}

void disableStepper() {
  resetA = 0;
  resetB = 0;
}

void enableStepper() {
  resetA = 1;
  resetB = 1;
}

void onAlarm() {
  buzzer.period_ms(1000);
  buzzer.write(0.5f);
}

void offAlarm() {
  buzzer.write(0);
}

void moveForward(int speed) {
  //stepperA.step(MOTOR_DISTANCE, 1, speed, false);
  stepperB.step(MOTOR_DISTANCE, 1, speed, false);
}

void moveBackward(int speed) {
  //stepperA.step(MOTOR_DISTANCE, 0, speed, false);
  stepperB.step(MOTOR_DISTANCE, 0, speed, false);
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
    default:
      break;
  }

  highPowerLED1 = 0;
  highPowerLED2 = 0;
  highPowerLED3 = 0;
  return;
}

void sendFeedback(string paraName,int para) {
  printf("{ \"%s\": %d }\n", paraName.c_str(), para);
}

void onPosition1() {
  disableStepper();
  sendFeedback("position", 1);
  wait_ms(350);
}

void onPosition2() {
  disableStepper();
  sendFeedback("position", 2);
  wait_ms(350);
}

void onPosition3() {
  disableStepper();
  sendFeedback("position", 3);
  wait_ms(350);
}

// void onPosition4() {
//   disableStepper();
//   sendFeedback("position", 4);
// }


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
    move = cJSON_GetObjectItem(json, "move")->valueint;
    trigger = cJSON_GetObjectItem(json, "trigger")->valueint;
    //speed = cJSON_GetObjectItem(json, "speed")->valueint;
    cJSON_Delete(json);
  }

  // Set COMMAND_FLAG to true, ready to handle inside main



  // Move Stepper Motor
  //printf("move is %d", move);
  if (move != 0) {
    COMMAND_FLAG = 1;
    //moveMotor(move, speed);
  }

  if (trigger !=0) {
    //triggerLED(trigger);
  }

  //printf("{ \"status\": \"ok\" }\n");
  //printf("command flag is %d", COMMAND_FLAG);
  //printf("%s\n", holder.c_str());
  // Restore ISR when everything is done:
  pc.attach(&readPC);
}


int main() {
  led2 = 1;
  resetA = 1;
  resetB = 1;
  pc.attach(&readPC);
  flipper.attach(&flip, 1); // the address of the function to be attached (flip) and the interval (2 seconds)
  //flipper2.attach(&flip2, 1);

  limitSwitch1.rise(&onPosition1);
  limitSwitch2.rise(&onPosition2);
  limitSwitch3.rise(&onPosition3);
  //limitSwitch4.rise(&onPosition4);

  // spin in a main loop. flipper will interrupt it to call flip
  //sawTooth.waveOut(1);

  led3.flash(1);
  led4.flash(3);

  while(1) {
    if (COMMAND_FLAG == 1) {
      //pc.printf("To Move Motor %d", move);
      COMMAND_FLAG = 0;
      moveMotor(move, speed);
      triggerLED(trigger);
    }
    //led3.flash(1);
    //led4.flash(3);
    //pc.printf("testing\n");
    wait(0.2f);
    // onAlarm();
    // wait(5.0f);
    // offAlarm();
    // for(float p=0; p<1.0; p += 0.1) {
    //   myServo = p;
    //   wait(0.2);
    // }
  }
}
