#include "mbed.h"
#include <string>
#include <cJSON.h>
#include <Flasher.h>
#include <SawTooth.h>
#include <Stepper.h>
Serial pc(USBTX, USBRX, 115200);

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

void flip2() {
  led1 = !led1;
}

void flip() {
  led2 = !led2;
}

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
  int period;
  int cycles;
  int stepsA, directionA, stepsB, directionB, speedA=300, speedB=300;
  double factor;

  char temp;
  while(temp != '\n') {
    temp = pc.getc();
    holder += temp;
  }
  if (holder.length() < 10) return;

  json = cJSON_Parse(holder.c_str());
  if (!json) {
    printf("Error before: [%s]\n", cJSON_GetErrorPtr());
  } else {
    period = cJSON_GetObjectItem(json, "period")->valueint;
    cycles = cJSON_GetObjectItem(json, "cycles")->valueint;
    factor = cJSON_GetObjectItem(json, "factor")->valuedouble;
    stepsA = cJSON_GetObjectItem(json, "stepsA")->valueint;
    directionA = cJSON_GetObjectItem(json, "directionA")->valueint;
    speedA = cJSON_GetObjectItem(json, "speedA")->valueint;
    stepsB = cJSON_GetObjectItem(json, "stepsB")->valueint;
    directionB = cJSON_GetObjectItem(json, "directionB")->valueint;
    speedB = cJSON_GetObjectItem(json, "speedB")->valueint;
    cJSON_Delete(json);
  }

  led1.period_ms(period);
  led1.write(0.5f);
  // Move Stepper Motor
  stepperA.step(stepsA, directionA, speedA, false);
  stepperB.step(stepsB, directionB, speedB, false);
  // Generate Wave
  sawTooth.setWave(factor, period);
  sawTooth.waveOut(cycles);
  printf("%s\n", holder.c_str());
  printf("period is %d ms\n", period);
  //led1 = !led1;
  // Restore ISR when everything is done:
  pc.attach(&readPC);
}



int main() {
  led2 = 1;
  pc.attach(&readPC);
  flipper.attach(&flip, 1); // the address of the function to be attached (flip) and the interval (2 seconds)
  //flipper2.attach(&flip2, 1);
  // spin in a main loop. flipper will interrupt it to call flip
  //sawTooth.waveOut(1);
  while(1) {
    //led3.flash(1);
    //led4.flash(3);
    //pc.printf("testing\n");
    //wait(1.0f);
  }
}
