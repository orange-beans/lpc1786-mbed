#ifndef __MAIN_H
#define __MAIN_H

//****** Note ******//
// this header file is used to define 
// RTOS related settings

//****** Define Constants ******//
#define REALTIME_TICK_S     0x01
#define COMMAND_S           0x02
#define INTERRUPT_S         0x03

#define LARGE_STACK_SIZE    4096
#define MEDIUM_STACK_SIZE   2048
#define SMALL_STACK_SIZE    1024
#define MINI_SMALL_SIZE     512

// This interval needs to be larger than MAX31855 poll interval
#define REALTIME_INTERVAL   200
#define INTERRUPT_INTERVAL  100

#define ON 1
#define OFF 0

#endif /* __MAIN_H */
