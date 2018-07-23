#include "mbed.h"
#include "mbed_events.h"
#include "main.h"
#include "profile.h"
#include <stdlib.h>
#include <sstream>
#include <string>
#include <Stepper.h>
#include <MAX31855.h>
#include <Adafruit_SSD1306.h>

//****** Configure User Variables ******//
string VERSION = "180716_01";
system_setting_t system_setting = { false, 10, {0,0,0,0}, 0, {0,0,0,0 ,0,0,0,0}, 0, {500, 500}, {0, 0}};
unsigned char COUNT_LIMIT = 1000/REALTIME_INTERVAL;
// find Command Token
string STARTDELIMITER = ":";
string STOPDELIMITER = "\n";

// HACK: check input pin
#define HOMING_SENSEOR 0x10
#define BUTTON_PRESSED 0x20
#define BUTTON_RELEASE 0x21
unsigned char dInTriggered = 0xff;

// HACK: process flags
unsigned char initDone = false;
unsigned char processDone = false;

//****** Define Function Pins ******//
// DigitalOut led1(LED1);
// DigitalOut led2(LED2);
// DigitalOut led3(LED3);
// DigitalOut led4(LED4);

// PWM Outputs
PwmOut pwmOut0(p21);
PwmOut pwmOut1(p22);

// Digital Outputs
BusOut digitalOuts(p23, p24, p25, p26, p27, p28, p29, p30, p17, p19);

// Digital Inputs
// BusIn digitalIns(PC_0, PC_1, PC_2, PC_3, PC_4, PC_5, PC_6, PC_7); // Change these pins to buttons on your board.

//InterruptIn digitalIn(PC_13);
DigitalIn digitalIn0(p13);
DigitalIn digitalIn1(p14);

// Analog Outputs
AnalogOut analogOut0(p18);

// Analog Inputs
AnalogIn analogIn0(p15);
AnalogIn analogIn1(p16);
// AnalogIn analogIn2(p17);
// AnalogIn analogIn3(p19);

// Stepper motor control
stepper stepper0(p5, p6);
DigitalOut stepper0En(p11);

stepper stepper1(p7, p8);
DigitalOut stepper1En(p12);

// Setup Serial Ports
Serial pc(USBTX, USBRX, 115200);

// Setup SPI
// SPI thermoSPI(PB_15, PB_14, PB_13);
// max31855 maxThermo(thermoSPI, PB_12);

// NOTE: 
// 1. PC_9 will cause problem, the program will not execute;
// 2. I2CPreInit not working;
// Setup I2C & OLED
// I2CPreInit gI2C(PB_9, PB_8);
I2C gI2C(p9, p10);
Adafruit_SSD1306_I2c gOled(gI2C, p20);

//****** Define Threads ******//
// Define threads
// NOTE: motor control thread has to be put at highest pority
Thread realtimeThread(osPriorityBelowNormal, MEDIUM_STACK_SIZE, NULL, NULL);
//Thread operateThread(osPriorityAboveNormal, MEDIUM_STACK_SIZE, NULL, NULL);
Thread displayTread(osPriorityBelowNormal, SMALL_STACK_SIZE, NULL, NULL);
Thread commandThread(osPriorityNormal, MEDIUM_STACK_SIZE, NULL, NULL);
Thread interruptThread(osPriorityNormal, MEDIUM_STACK_SIZE, NULL, NULL);

// TEMP process Thread
Thread processThread(osPriorityAboveNormal, MEDIUM_STACK_SIZE, NULL, NULL);

// Define threads functions
void realtimeHandle();
void commandHandle();
void displayHandle();
void interruptHandle();
void processHandle();

//****** Define ISR ******//
void commandISR();
void realtimeTick();
void interruptTick();
void externalISR();

//****** Define Mails ******//
typedef struct {
  float   temperature;
  float   output;
} mail_t;

typedef struct {
  char *cmdStr;
} CC_t;

// NOTE: for STM32F410, more than 10 char recevied will cause system stop.
// changed Mail size to 8 solved this issue
Mail<mail_t, 4> mail_box;
Mail<CC_t, 10> CC_box;

//****** Define Events ******//
EventFlags event;

//****** Define Queues ******//
//EventQueue queue(32 * EVENTS_EVENT_SIZE);

//****** Local Helpers ******//
// isSubString
bool isSubString(string str1, string str2) {
  return str1.find(str2) != std::string::npos;
}

void parseToken(string str, token_t * tokenHolder) {
  unsigned int first = str.find(STARTDELIMITER) + 1;
  unsigned int last = str.find(STOPDELIMITER) - 1;
  string token = str.substr(first, last-first);

  tokenHolder->intValue = atoi(token.c_str());
  tokenHolder->floatValue = atof(token.c_str());
}

int parseTokenInt(string str) {
  unsigned int first = str.find(STARTDELIMITER) + 1;
  unsigned int last = str.find(STOPDELIMITER) - 1;
  string token = str.substr(first, last-first);
  return atoi(token.c_str());
}

double parseTokenDouble(string str) {
  unsigned int first = str.find(STARTDELIMITER) + 1;
  unsigned int last = str.find(STOPDELIMITER) - 1;
  string token = str.substr(first, last-first);

  return atof(token.c_str());
}

void sendPC(string message) {
  pc.printf("{%s}\n", message.c_str());
}

void setPWM() {
  // Set PWM period
  pwmOut0.period_ms(system_setting.pwmPeriod);
  pwmOut1.period_ms(system_setting.pwmPeriod);
  // pwmOut2.period_ms(system_setting.pwmPeriod);
  // pwmOut3.period_ms(system_setting.pwmPeriod);

  pc.printf("ACK:%d\r\n", system_setting.pwmPeriod);

  wait_ms(2);

  // Set PWM dutycycle
  pwmOut0.write((float)system_setting.pwmOuts[0]);
  pwmOut1.write((float)system_setting.pwmOuts[1]);
  // pwmOut2.write((float)system_setting.pwmOuts[2]);
  // pwmOut3.write((float)system_setting.pwmOuts[3]);
}

void setDouts() {
  digitalOuts = system_setting.dOutsByte;
  // pc.printf("ACK:%d\r\n", system_setting.dOutsByte);
}

void readDins() {
  pc.printf("ACK:%02X %02X\r\n", digitalIn0.read(), digitalIn1.read());
}

void readAin(unsigned char channel) {
  if (channel == 0) pc.printf("ACK:%3.3f\r\n", analogIn0.read());
  if (channel == 1) pc.printf("ACK:%3.3f\r\n", analogIn1.read());
  // if (channel == 2) pc.printf("ACK:%3.3f\r\n", analogIn2.read());
  // if (channel == 3) pc.printf("ACK:%3.3f\r\n", analogIn3.read());
}

void setAout() {
  analogOut0.write(system_setting.aOutValue);
}

void moveStepper0(int speed, int distance = MOTOR_DISTANCE) {
  if (distance >0) stepper0.step(distance, 1, speed, false);
  else stepper0.step(abs(distance), 0, speed, false);
}

void moveStepper1(int speed, int distance = MOTOR_DISTANCE) {
  pc.printf("Stepper1 run\r\n");
  if (distance >0) stepper1.step(distance, 1, speed, false);
  else stepper1.step(abs(distance), 0, speed, false);
}

void enableStepper0() {
  stepper0En = 1;
}

void disableStepper0() {
  stepper0En = 0;
}

void enableStepper1() {
  stepper1En = 1;
}

void disableStepper1() {
  stepper1En = 0;
}

//****** System Init ******//
void initSystem() {

  pc.printf("Version: %s\r\n", VERSION.c_str());

  // MAX31855 init
  // maxThermo.initialise();

  // digitalIns.mode(PullNone); 

  pwmOut0.period_ms(100);
  pwmOut1.period_ms(100);
  // pwmOut2.period_ms(10);
  // pwmOut3.period_ms(10);

  pwmOut0.write(0);
  pwmOut1.write(0);
  // pwmOut2.write(0);
  // pwmOut3.write(0);

  enableStepper0();
  enableStepper1();

  // Init OLED
  gOled.clearDisplay();
  gOled.setTextCursor(0,0);
  // gOled.printf("setpoint is: %3.1f\r\n", heater_setting.setpoint);
  gOled.printf("CC's controller %3.2f\r\n", 123.45);
  // gOled.printf("powerOutput: %3.1f%%\r\n", output*100);
  gOled.display();
}

//****** Temp Process Control ******//
void reportStep(unsigned int stepNum, string message = "Running") {
  pc.printf("Step %d: %s\r\n", stepNum, message.c_str());
  // Print to OLED
  gOled.clearDisplay();
  gOled.setTextCursor(0,0);
  gOled.printf("SMF DNA Extractor\r\n");
  gOled.setTextCursor(0,8);
  gOled.printf("Step %d\r\n", stepNum);
  gOled.printf("%s\r\n", message.c_str());
  // NOTE: somehow display() need to be called twice, otherwise it will skip display
  gOled.display();
  gOled.display();
}

void onPump() {
  pwmOut0.write(1);
}

void onPumpHalf(double voltage) {
  pwmOut0.write(voltage/12);
}

void offPump() {
  pwmOut0.write(0);
}

void moveStepper(int steps) {
  enableStepper1();
  pc.printf("Moving Stepper:%d\r\n", stepper1En.read());
  moveStepper1(system_setting.motorSpeed[1], steps);
}

void onDout(unsigned int outPin) {
  system_setting.dOutsByte |= 1UL << outPin;
  setDouts();
}

void offDout(unsigned int outPin) {
  system_setting.dOutsByte &= ~(1UL << outPin);
  setDouts();
}

void processWait(unsigned int delayInS) {
  Thread::wait(delayInS * 1000);
}

void runWashing(unsigned int num) {
  // ********************* //
  // Step3: Washing 1
  // ********************* //
  reportStep(num, "Washing");
  
  // Step 3.1
  reportStep(num, "Washing 1/6");
  offDout(0);
  processWait(5);
  
  // Step 3.2
  reportStep(num, "Washing 2/6");
  offDout(5);
  processWait(20); // 20s for cooling down
  
  // Step 3.3
  reportStep(num, "Washing 3/6");

  // Mixing
  onDout(9);
  processWait(5);
  offDout(9);
  processWait(1);
  onDout(9);
  processWait(5);
  
  // Step 3.4
  reportStep(num, "Washing 4/6");
  onDout(5);
  processWait(60); // 60s
  
  // Step 3.5
  reportStep(num, "Washing 5/6");
  onDout(0);
  processWait(1);
  
  // Step 3.6
  reportStep(num, "Washing 6/6");
  // moveStepper(-160); // 36 degree
  moveStepper(-154);
  processWait(5);
}

void processHandle() {
  // unsigned char initDone = false;
  // unsigned char processDone = false;

  // while(true) {
  //   onDout(9);
  //   processWait(10);
  //   offDout(9);
  //   processWait(10);
  //   processWait(1);
  // }

  pc.printf("Process Started\r\n");

  while(true) {

    // Init process
    if (initDone != true) {
      // STEP 0: Initialization
      // digitalOuts = 31;
      // onPump();
      // processWait(2);
      // digitalOuts = 992;
      // offPump();
      // processWait(2);
      // digitalOuts = 0;

      reportStep(0, "Initialization");
      onPump();
      onDout(0);
      onDout(7);
      processWait(2);

      // Check homing
      if (digitalIn0.read() == LOW) {
        moveStepper(1000);
        processWait(3);
        moveStepper(30);
      }
      
      enableStepper1();
      reportStep(0, "Press button to start");
      initDone = true;
    }

    // Wait for start signal from Button
    event.wait_all(PROCESS_S);
    reportStep(1, "Process starting");
    processWait(2);

    // Process
    if (processDone != true) {
      // ********************* //
      // Step 1: Lysis
      // ********************* //
      reportStep(1, "Lysis");

      // Reduce Pump power
      onPumpHalf(8);

      // Step 1.1
      reportStep(1, "Lysis 1/4");
      onDout(1); // NOTE: temp off ultrasonic
      processWait(5);
      offDout(1);
      
      // Step 1.2
      reportStep(1, "Lysis 2/4");
      onDout(2);
      processWait(2);
      onDout(4);
      processWait(30);
      offDout(2);
      offDout(4);
      

      // Step 1.3
      onPumpHalf(8);
      reportStep(1, "Lysis 3/4");
      onDout(3);
      processWait(2);
      onDout(4);
      processWait(20);
      offDout(3);
      offDout(4);
      

      // Step 1.4
      reportStep(1, "Lysis 4/4");
      onDout(4);
      processWait(20);
      offDout(4);

      // Restore to full power
      onPump();

      // ********************* //
      // Step 2: Beads-Homo
      // ********************* //
      reportStep(2, "Beads-Homo");

      // Step 2.1
      reportStep(2, "Beads-Homo 1/5");
      offDout(0);
      processWait(5);
      
      // Step 2.2
      reportStep(2, "Beads-Homo 2/5");
      // Mixing
      onDout(9);
      processWait(5);
      offDout(9);
      processWait(1);
      onDout(9);
      processWait(5);

      processWait(60);  // Incubation time 60s
      
      // Step 2.3
      reportStep(2, "Beads-Homo 3/5");
      onDout(5);
      processWait(60); // 60s

      // Step 2.4
      reportStep(2, "Beads-Homo 4/5");
      onDout(0);
      processWait(1);
      
      // Step 2.5
      reportStep(2, "Beads-Homo 5/5");
      moveStepper(-160);
      processWait(5);
      
      // ********************* //
      // Step 3: Washing 1
      // ********************* //
      runWashing(3);

      // ********************* //
      // Step 4: Washing 2
      // ********************* //
      runWashing(4);

      // ********************* //
      // Step 5: Washing 3
      // ********************* //
      runWashing(5);

      // ********************* //
      // Step 6: Washing 4
      // ********************* //
      runWashing(6);

      // ********************* //
      // Step 7: Elution
      // ********************* //
      reportStep(7, "Elution");

      // Step 7.1
      reportStep(7, "Elution 1/6");
      onDout(6);
      processWait(60); // 60s
      offDout(6);
      
      // Step 7.2
      reportStep(7, "Elution 2/6");
      offDout(0);
      processWait(5);
      
      // Step 7.3
      reportStep(7, "Elution 3/6");
      offDout(5);
      processWait(20); // 20s for cooling
      
      // Step 7.4
      reportStep(7, "Elution 4/6");
      
      // Mixing
      onDout(9);
      processWait(5);
      offDout(9);
      processWait(1);
      onDout(9);
      processWait(5);

      // Step 7.5
      reportStep(7, "Elution 5/6");
      onDout(5);
      processWait(60);  // 60s

      // Step 7.6
      reportStep(7, "Elution 6/6");
      onDout(0);
      processWait(1);

      // ********************* //
      // Step 8: End
      // ********************* //
      if (digitalIn0.read() == LOW) {
        moveStepper(1000);
        processWait(3);
        moveStepper(30);
      }

      offDout(5);
      digitalOuts = 1;

      reportStep(8, "End");

      processDone = true;
    }

    // Wait forever
    Thread::wait(100);
  }
}

int main() {
  // Init System
  initSystem();

  // ISR handlers
  pc.attach(&commandISR);
  //digitalIn.fall(&externalISR);

  // Create a queue with the default size
  EventQueue queue;
  //queue.call_in(2000, printf, "called in 2 seconds\n");
  //queue.call_every(1000, blink, "called every 1 seconds\n\r");
  
  // HACK: Disable realtimeTick
  // queue.call_every(REALTIME_INTERVAL, realtimeTick);
  queue.call_every(INTERRUPT_INTERVAL, interruptTick);

  // HACK: disable realtimeHandle and commandHandle
  // Start Threads
  // realtimeThread.start(realtimeHandle);
  // commandThread.start(commandHandle);
  interruptThread.start(interruptHandle);
  //displayTread.start(displayHandle);

  processThread.start(processHandle);

  // events are executed by the dispatch method
  queue.dispatch();

  // NOTE: main thread is at osPriorityNormal, without a threadWait, any thread below Normal will
  // never be executed
  while(true) {
    // put your main code here, to run repeatedly:
  }
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

    // Increment counter for each realtime tick
    counter += 1;

    // sent_mail = mail_box.alloc();
    // sent_mail->temperature = temperature;
    // sent_mail->output = output;
    // mail_box.put(sent_mail);

    gOled.clearDisplay();
    gOled.setTextCursor(0,0);
    // gOled.printf("setpoint is: %3.1f\r\n", heater_setting.setpoint);
    gOled.printf("Current stage %d\r\n", counter);
    // gOled.printf("powerOutput: %3.1f%%\r\n", output*100);
    gOled.display();

    // 2.Do realtime tasks
    if (system_setting.isChanged == true) {
      sendPC("Executing Command");

      pc.printf("Before, %d \r\n", system_setting.motorDistance[1]);
      // setPWM();
      // setDouts();
      // setAout();
      if (system_setting.motorDistance[0] != 0) {
        moveStepper0(system_setting.motorSpeed[0], system_setting.motorDistance[0]);
        system_setting.motorDistance[0] = 0;
      }
      if (system_setting.motorDistance[1] != 0) {
        moveStepper1(system_setting.motorSpeed[1], system_setting.motorDistance[1]);
        system_setting.motorDistance[1] = 0;
      }

      // reset some flags
      system_setting.isChanged = false;
      enableStepper0();
      enableStepper1();
      // system_setting.motorDistance = 0;
    }
  }
}

void interruptHandle() {
    while(true) {
    // 1.Wait until interrupts
    event.wait_all(INTERRUPT_S);

    // 2.Do tasks
    pc.printf("External Interrupt triggered:%d\r\n", dInTriggered);

    // TODO: test disable steppers
    if (dInTriggered == HOMING_SENSEOR) {
      disableStepper0();
      disableStepper1();
    }

    if (dInTriggered == BUTTON_PRESSED) {
      event.set(PROCESS_S);
    }

    if (dInTriggered == BUTTON_RELEASE) {
      // Reset process
      initDone = false;
      processDone = false;
    }
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

    //led2 = !led2;
  }
}

void commandHandle() {
  osEvent evt;
  CC_t *received_cmd;

  string holder;
  token_t tokenHolder = {0, 0};

  unsigned char command = 0;
  // cJSON *json;

  while(true) {
    //event.wait_all(COMMAND_S);
    command = 0;

    evt = CC_box.get();
    if (evt.status == osEventMail) {
      received_cmd = (CC_t*)evt.value.p;
      CC_box.free(received_cmd);

      // Process command
      holder = received_cmd->cmdStr;

      // NOTE: cannot directly return from a ISR
      if (holder.length() < 5) command = ERR_CC_TOOSHORT;

      if (isSubString(holder, "CC_ID")) command = CC_ID;
      if (isSubString(holder, "CC_ON_DOUT:")) command = CC_ON_DOUT;
      if (isSubString(holder, "CC_OFF_DOUT:")) command = CC_OFF_DOUT;
      if (isSubString(holder, "CC_DOUTS:")) command = CC_SET_DOUTS;

      if (isSubString(holder, "CC_READ_DINS")) command = CC_READ_DINS;

      if (isSubString(holder, "CC_READ_AIN:")) command = CC_READ_AIN;
      if (isSubString(holder, "CC_SET_AOUT:")) command = CC_SET_AOUT;

      if (isSubString(holder, "CC_PERIOD:")) command = CC_PWM_PERIOD;
      if (isSubString(holder, "CC_PWM0:")) command = CC_PWM0;
      if (isSubString(holder, "CC_PWM1:")) command = CC_PWM1;
      // if (isSubString(holder, "CC_PWM2:")) command = CC_PWM2;
      // if (isSubString(holder, "CC_PWM3:")) command = CC_PWM3;

      if (isSubString(holder, "CC_MOTOR0_CW:")) command = CC_MOTOR0_CW;
      if (isSubString(holder, "CC_MOTOR0_CCW:")) command = CC_MOTOR0_CCW;
      if (isSubString(holder, "CC_MOTOR0_SPEED:")) command = CC_MOTOR0_SPEED;

      if (isSubString(holder, "CC_MOTOR1_CW:")) command = CC_MOTOR1_CW;
      if (isSubString(holder, "CC_MOTOR1_CCW:")) command = CC_MOTOR1_CCW;
      if (isSubString(holder, "CC_MOTOR1_SPEED:")) command = CC_MOTOR1_SPEED;

      // Parse RS485 commands
      switch (command) {
        case CC_ID:
          sendPC("ACK");
          break;

        case CC_ON_DOUT:
          parseToken(holder.c_str(), & tokenHolder);

          if (tokenHolder.intValue >= 0 && tokenHolder.intValue <=9 ) {
            system_setting.dOutsByte |= 1UL << tokenHolder.intValue;
            setDouts();
          } else {
            sendPC("ERR:INVALID_DOUT_NO");
          }
          break;

        case CC_OFF_DOUT:
          parseToken(holder.c_str(), & tokenHolder);

          if (tokenHolder.intValue >= 0 && tokenHolder.intValue <= 9) {
            system_setting.dOutsByte &= ~(1UL << tokenHolder.intValue);
            setDouts();
          } else {
            sendPC("ERR:INVALID_DOUT_NO");
          }
          break;

        case CC_SET_DOUTS:
          parseToken(holder.c_str(), & tokenHolder);

          if (tokenHolder.intValue >= 0 && tokenHolder.intValue <=1023 ) {
            system_setting.dOutsByte = tokenHolder.intValue;
            setDouts();
          } else {
            sendPC("ERR:INVALID_DOUT_BYTE");
          }
          break;  

        case CC_READ_DINS:
          readDins();
          break;

        case CC_READ_AIN:
          parseToken(holder.c_str(), & tokenHolder);

          if (tokenHolder.intValue >= 0 && tokenHolder.intValue <=1 ) {
            readAin(tokenHolder.intValue);
          } else {
            sendPC("ERR:INVALID_AIN_NO");
          }
          break;  

      case CC_SET_AOUT:
          parseToken(holder.c_str(), & tokenHolder);

          if (tokenHolder.floatValue >=0 && tokenHolder.floatValue <=1) {
            system_setting.aOutValue = tokenHolder.floatValue;
            setAout();
          } else {
            sendPC("ERR:INVALID_AOUT_VALUE");
          }
          break;      

        case CC_PWM_PERIOD:
          parseToken(holder.c_str(), & tokenHolder);

          if (tokenHolder.intValue >= 1 && tokenHolder.intValue <= 10000) {
            system_setting.pwmPeriod = tokenHolder.intValue;
            setPWM();
          } else {
            sendPC("ERR:INVALID_PWM_PERIOD");
          }

          break;  

        case CC_PWM0:
          parseToken(holder.c_str(), & tokenHolder);

          if (tokenHolder.floatValue >=0 && tokenHolder.floatValue <=1) {
            system_setting.pwmOuts[0] = tokenHolder.floatValue;
            setPWM();
          } else {
            sendPC("ERR:INVALID_PWM_DUTYCYCLE");
          }
          break;

        case CC_PWM1:
          parseToken(holder.c_str(), & tokenHolder);

          if (tokenHolder.floatValue >=0 && tokenHolder.floatValue <=1) {
            system_setting.pwmOuts[1] = tokenHolder.floatValue;
            setPWM();
          } else {
            sendPC("ERR:INVALID_PWM_DUTYCYCLE");
          }
          break;

        // case CC_PWM2:
        //   parseToken(holder.c_str(), & tokenHolder);

        //   if (tokenHolder.floatValue >=0 && tokenHolder.floatValue <=1) {
        //     system_setting.pwmOuts[2] = tokenHolder.floatValue;
        //     setPWM();
        //   } else {
        //     sendPC("ERR:INVALID_PWM_DUTYCYCLE");
        //   }
        //   break;

        // case CC_PWM3:
        //   parseToken(holder.c_str(), & tokenHolder);

        //   if (tokenHolder.floatValue >=0 && tokenHolder.floatValue <=1) {
        //     system_setting.pwmOuts[3] = tokenHolder.floatValue;
        //     setPWM();
        //   } else {
        //     sendPC("ERR:INVALID_PWM_DUTYCYCLE");
        //   }
        //   break;

        case CC_MOTOR0_CW:
          parseToken(holder.c_str(), & tokenHolder);

          if (tokenHolder.intValue > 0 && tokenHolder.intValue <=5000) {
            system_setting.isChanged = true;
            system_setting.motorDistance[0] = tokenHolder.intValue;
          } else {
            sendPC("ERR:INVALID_MOTOR_DISTANCE");
          }
          break;

        case CC_MOTOR0_CCW:
          parseToken(holder.c_str(), & tokenHolder);

          if (tokenHolder.intValue > 0 && tokenHolder.intValue <=5000) {
            system_setting.isChanged = true;
            system_setting.motorDistance[0] = -1 * tokenHolder.intValue;
          } else {
            sendPC("ERR:INVALID_MOTOR_DISTANCE");
          }
          break;

        case CC_MOTOR0_SPEED:
          parseToken(holder.c_str(), & tokenHolder);

          if (tokenHolder.intValue >= 1 & tokenHolder.intValue <=1300) {
            system_setting.motorSpeed[0] = tokenHolder.intValue;
          } else {
            sendPC("ERR:INVALID_MOTOR_SPEED");
          }
          break;

        case CC_MOTOR1_CW:
          parseToken(holder.c_str(), & tokenHolder);

          if (tokenHolder.intValue > 0 && tokenHolder.intValue <=5000) {
            system_setting.isChanged = true;
            system_setting.motorDistance[1] = tokenHolder.intValue;
          } else {
            sendPC("ERR:INVALID_MOTOR_DISTANCE");
          }
          break;

        case CC_MOTOR1_CCW:
          parseToken(holder.c_str(), & tokenHolder);

          if (tokenHolder.intValue > 0 && tokenHolder.intValue <=5000) {
            system_setting.isChanged = true;
            system_setting.motorDistance[1] = -1 * tokenHolder.intValue;
          } else {
            sendPC("ERR:INVALID_MOTOR_DISTANCE");
          }
          break;

        case CC_MOTOR1_SPEED:
          parseToken(holder.c_str(), & tokenHolder);

          if (tokenHolder.intValue >= 1 & tokenHolder.intValue <=1300) {
            system_setting.motorSpeed[1] = tokenHolder.intValue;
          } else {
            sendPC("ERR:INVALID_MOTOR_SPEED");
          }
          break;

        default:
          sendPC("ERR:UNKNOWN_CMD");
          break;
      }
    }
  }
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

  // sendPC(holder.c_str());

  CC_t *sent_cmd = CC_box.alloc();
  strcpy(sent_cmd->cmdStr, holder.c_str());
  CC_box.put(sent_cmd);
}

void realtimeTick() {
  // led1 = !led1;
  event.set(REALTIME_TICK_S);
}

unsigned char pinRecord0 = LOW;
unsigned char pinRecord1 = HIGH;

void interruptTick() {
  if (digitalIn0.read() == HIGH && pinRecord0 == LOW) {
    dInTriggered = HOMING_SENSEOR;
    event.set(INTERRUPT_S);
  }

  // Button pressed: high to low
  if (digitalIn1.read() == LOW && pinRecord1 == HIGH) {
    dInTriggered = BUTTON_PRESSED;
    event.set(INTERRUPT_S);
  }

  // Button released: low to high
  if (digitalIn1.read() == HIGH && pinRecord1 == LOW) {
    dInTriggered = BUTTON_RELEASE;
    event.set(INTERRUPT_S);
  }
  
  pinRecord0 = digitalIn0.read();
  pinRecord1 = digitalIn1.read();
}