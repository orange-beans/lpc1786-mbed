#include "mbed.h"
#include "Flasher.h"

Ticker flipper;
Ticker flipper2;
DigitalOut led1(LED1);
DigitalOut led2(LED2);
//DigitalOut led3(LED3);
//DigitalOut led4(LED4);


void flip2() {
  led1 = !led1;
}

void flip() {
  led2 = !led2;
}

Flasher led3(LED3);
Flasher led4(LED4, 2);

int main() {
  led2 = 1;
  flipper.attach(&flip, 1); // the address of the function to be attached (flip) and the interval (2 seconds)
  flipper2.attach(&flip2, 1);
  // spin in a main loop. flipper will interrupt it to call flip
  while(1) {
    led3.flash(3);
    led4.flash();
  }
}
