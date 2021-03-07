#include <stdint.h>
#include <stdbool.h>
// includes da biblioteca driverlib
#include "driverlib/systick.h"
#include "driverleds.h" // Projects/drivers

// MEF com apenas 2 estados e 1 evento temporal que alterna entre eles
// Seleção por evento

typedef enum {zero,um,dois,tres,quatro,cinco,seis,sete} state_t;

volatile uint8_t Evento = 0;

void SysTick_Handler(void){
  Evento = 1;
} // SysTick_Handler

void main(void){
  static state_t Estado = zero; // estado inicial da MEF
  
  LEDInit(LED1);
  LEDInit(LED2);
  LEDInit(LED3);
  SysTickPeriodSet(12000000); // f = 1Hz para clock = 24MHz
  SysTickIntEnable();
  SysTickEnable();

  while(1){
    if(Evento){
      switch(Estado){
        case zero:
          LEDOff(LED1);
          LEDOff(LED2);
          LEDOff(LED3);
          Estado = um;
          break;
        case um:
          LEDOn(LED1);
          Estado = dois;
          break;
        case dois:
          LEDOn(LED2);
          Estado = tres;
          break;
        case tres:
          LEDOff(LED1);
          Estado = quatro;
          break;
        case quatro:
          LEDOn(LED3);
          Estado = cinco;
          break;
        case cinco:
          LEDOn(LED1);
          Estado = seis;
          break;
        case seis:
          LEDOff(LED2);
          Estado = sete;
          break;
        case sete:
          LEDOff(LED1);
          Estado = zero;
          break;
      } // switch
    } // if
    Evento = 0;
  } // while
} // main
