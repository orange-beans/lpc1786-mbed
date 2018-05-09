#include "mbed.h"
#include "mbed_events.h"
#include "main.h"
#include <stdlib.h>
#include <string>
#include <cJSON.h>
// #include <Flasher.h>
// #include <PID.h>

//****** Define User Variables ******//
typedef struct {
  unsigned int valve1;
  unsigned int valve2;
  unsigned int valve3;
  unsigned int valve4;
  unsigned int valve5;
  unsigned int valve6;
  unsigned int valve7;
  unsigned int valve8;
  unsigned int valve9;
  unsigned int valve10;
} system_setting_t;

system_setting_t system_setting = { 0,0,0,0,0 ,0,0,0,0,0 };

unsigned char COUNT_LIMIT = 1000/REALTIME_INTERVAL;

//****** Define Commands ******//
#define CMD_CC_ID 0x10

#define CMD_CC_ON_VALVE   0x30
#define CMD_CC_OFF_VALVE  0x31

#define CMD_CC_ROTATE_MOTOR 0x40
#define CMD_CC_HOME_MOTOR   0x41

#define CMD_CC_ON_ULTRA  0x50
#define CMD_CC_OFF_ULTRA 0x51

#define CMD_CC_ON_PUMP   0x60
#define CMD_CC_OFF_PUMP  0x61

#define ERR_CC_CMD_UNKNOWN 0xf0
#define ERR_CC_CMD_TOOSHORT 0xf1

//****** Define Function Pins ******//
DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut statusLED(p26);

// ID reading
DigitalIn ID_0(p8);
DigitalIn ID_1(p7);
DigitalIn ID_2(p6);
DigitalIn ID_3(p5);

//ADC pins
AnalogIn analogInA(p15);
AnalogIn analogInB(p16);

//PWM pins
PwmOut heater(p21);
PwmOut cooler(p22);

// Setup Serial Ports
Serial pc(USBTX, USBRX, 115200);
//Serial dev(p28, p27, 115200);

//****** Define Threads ******//
// Define threads
Thread realtimeThread(osPriorityRealtime, MEDIUM_STACK_SIZE, NULL, NULL);
//Thread operateThread(osPriorityAboveNormal, MEDIUM_STACK_SIZE, NULL, NULL);
Thread displayTread(osPriorityBelowNormal, MEDIUM_STACK_SIZE, NULL, NULL);
Thread commandThread(osPriorityNormal, MEDIUM_STACK_SIZE, NULL, NULL);

// Define threads functions
void realtimeHandle();
void commandHandle();
void displayHandle();

void realtimeTick();
//****** Define ISR ******//
void commandISR();

//****** Define Mails ******//
typedef struct {
  float   temperature;
  float   output;
} mail_t;

typedef struct {
  char *cmdStr;
} cmd_t;

Mail<mail_t, 4> mail_box;
Mail<cmd_t, 4> cmd_box;

//****** Define Events ******//
EventFlags event;

//****** Define Queues ******//
//EventQueue queue(32 * EVENTS_EVENT_SIZE);

//****** Local Helpers ******//
// isSubString
bool isSubString(string str1, string str2) {
  return str1.find(str2) != std::string::npos;
}

// find Command Token
string STARTDELIMITER = ":";
string STOPDELIMITER = "\n";

string findToken(string str) {
  unsigned int first = str.find(STARTDELIMITER) + 1;
  unsigned int last = str.find(STOPDELIMITER) - 1;
  string token = str.substr(first, last-first);
  return token;
}

void sendPC(string message) {
  pc.printf("{%s}\n", message.c_str());
}

//****** System Init ******//
void initSystem() {

}

//****** Main ******//
int main() {
  // Init System
  initSystem();

  // ISR handlers
  pc.attach(&commandISR);

  // Create a queue with the default size
  EventQueue queue;
  //queue.call_in(2000, printf, "called in 2 seconds\n");
  queue.call_every(REALTIME_INTERVAL, realtimeTick);
  //queue.call_every(1000, blink, "called every 1 seconds\n\r");

  // Start Threads
  realtimeThread.start(realtimeHandle);
  //displayTread.start(callback(displayHandle, &led1));
  commandThread.start(commandHandle);
  //displayTread.start(displayHandle);

  // events are executed by the dispatch method
  queue.dispatch();

  while(true) {}
}

//****** Threads Callbacks ******//
void realtimeHandle() {
  float output = 0, temperature = 0;
  unsigned char counter = 0;
  mail_t *sent_mail;

  // Temp
  unsigned int holdCounter = 0;

  while(true) {
    // 1.Wait until timer tick
    event.wait_all(REALTIME_TICK_S);

    // sent_mail = mail_box.alloc();
    // sent_mail->temperature = temperature;
    // sent_mail->output = output;
    // mail_box.put(sent_mail);

    // 2.Do realtime tasks
    // sendPC("realtime");
  }
}

void displayHandle() {
  osEvent evt;
  mail_t *received_mail;
  float temperature, output;
  while(true) {
    // Wait for mail to be avaliable;
    evt = mail_box.get();
    // Read mail
    if (evt.status == osEventMail) {
      received_mail = (mail_t*)evt.value.p;
      temperature = received_mail->temperature;
      output = received_mail->output;
      // Free memory
      // NOTE: need to process data before free, otherwise data may get corrupted
      mail_box.free(received_mail);
      // printf("0x%04x/temperature read is: %3.1f\r\n", BACKBONE_ADDRESS, temperature);
      // printf("0x%04x/output setting is: %3.1f%%\r\n", BACKBONE_ADDRESS, output*100);
      // printf("0x%04x/heater setpoint is: %3.1f\r\n", BACKBONE_ADDRESS, heater_setting.setpoint);
    }

    led2 = !led2;
  }
}

void commandHandle() {
  osEvent evt;
  cmd_t *received_cmd;

  string holder, token;
  unsigned char command = 0;
  cJSON *json;
  unsigned char cmd_address = 0xffff;

  while(true) {
    //event.wait_all(COMMAND_S);
    // reset cmd_address everytime
    cmd_address = 0xffff;
    command = 0;

    evt = cmd_box.get();
    if (evt.status == osEventMail) {
      received_cmd = (cmd_t*)evt.value.p;
      cmd_box.free(received_cmd);
      // Process command

      holder = received_cmd->cmdStr;

      // NOTE: cannot directly return from a ISR
      if (holder.length() < 5) command = ERR_CC_CMD_TOOSHORT;

      if (isSubString(holder, "cc_ID")) command = CMD_CC_ID;
      if (isSubString(holder, "cc_ON_VALVE:")) command = CMD_CC_ON_VALVE;
      if (isSubString(holder, "cc_OFF_VALVE:")) command = CMD_CC_OFF_VALVE;

      // Parse RS485 commands
      switch (command) {
        case CMD_CC_ID:
          sendPC("cc_ACK");
          break;

        case CMD_CC_ON_VALVE:
          token = findToken(holder.c_str());
          sendPC("cc_ACK_VALVE_ON:" + token);
          break;

        case CMD_CC_OFF_VALVE:
          token = findToken(holder.c_str());
          sendPC("cc_ACK_VALVE_OFF:" + token);
          break;

        default:
          sendPC("cc_UNKNOWN_CMD");
          break;
      }
    }
  }
}

void realtimeTick() {
  led1 = !led1;
  statusLED = !statusLED;
  event.set(REALTIME_TICK_S);
}

//****** ISR handles ******//
void commandISR() {
  //event.set(COMMAND_S);
  string holder;
  char temp;

  while(temp != '\n') {
    temp = pc.getc();
    holder += temp;
  }

  //printf("%s\n", holder.c_str());

  cmd_t *sent_cmd = cmd_box.alloc();
  strcpy(sent_cmd->cmdStr, holder.c_str());
  cmd_box.put(sent_cmd);
}
