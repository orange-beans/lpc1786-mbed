#include "mbed.h"
#include <string>
#include <cJSON.h>
#include <Flasher.h>
Serial pc(USBTX, USBRX);

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

void readPC() {
  // Note: you need to actually read from the serial to clear the RX interrupt
  //char _buffer[128];
  string test_str = "{\"name\":5}";
  string holder;
  //string temp;
  cJSON *json;
  int count;
  json = cJSON_Parse(test_str.c_str());
  if (!json) {
    printf("Error before: [%s]\n", cJSON_GetErrorPtr());
    //wait(2.0);
  } else {
    count = cJSON_GetObjectItem(json, "name")->valueint;
    cJSON_Delete(json);
  }
  char temp;
  while(temp != '\n') {
    temp = pc.getc();
    holder += temp;
    //pc.gets(_buffer, 4);
    //temp += _buffer;
  }
  //printf("%s\n", temp.c_str());
  printf("%s\n", holder.c_str());
  printf("%d\n", count);
  led1 = !led1;
}

Flasher led3(LED3);
Flasher led4(LED4, 2);

int main() {
  led2 = 1;
  pc.attach(&readPC);
  flipper.attach(&flip, 1); // the address of the function to be attached (flip) and the interval (2 seconds)
  //flipper2.attach(&flip2, 1);
  // spin in a main loop. flipper will interrupt it to call flip
  while(1) {
    led3.flash(1);
    led4.flash();
    pc.printf("testing\n");
    //wait(1.0f);
  }
}
