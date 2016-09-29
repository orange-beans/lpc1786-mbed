#include "mbed.h"

DigitalOut myled1(LED1);
DigitalOut myled2(LED2);

PwmOut myled3(LED3);

const float DELAY_TIME = 0.012;

int main() {

  myled3.period(0.02);
  myled3.write(0.1);

  while(1) {
      myled1 = 1;
      myled2 = 0;
      wait(DELAY_TIME);
      myled1 = 0;
      myled2 = 1;
      wait(DELAY_TIME);
  }
}
