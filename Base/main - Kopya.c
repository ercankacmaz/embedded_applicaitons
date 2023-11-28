#include <stdio.h>
#include <stdint.h>

#include "system.h"
#include "io.h"



void init(void)
{
  // I/O protlari baslangiç
  sys_ioInit();
  
  // System Clock Tick
  
  // LED baslangiç
  IO_Write(IOP_LED, 1);
  IO_Init(IOP_LED, IO_MODE_OUTPUT_OD);
}
  
  void Task_LED(void)
{
  static enum {
    I_LED_ON,
    S_LED_ON,
    I_LED_OFF,
    S_LED_OFF,
  } state = I_LED_ON;
  
  static clock_t t0, t1;
  
  t1 = clock();
  
  switch (state) {
  case I_LED_ON:
    IO_Write(IOP_LED, 0);  // LED on
    t0 = t1;
    state = S_LED_ON;
    break;
    
  case S_LED_ON:
    if(t1 - t0 >= CLOCKS_PER_SEC / 10)
      state = I_LED_OFF;
    break;
    
  case I_LED_OFF:
    IO_Write(IOP_LED, 1);  // LED off
    t0 = t1;
    state = S_LED_OFF;
    break;
    
  case S_LED_OFF:
    if ( t1 - t0 >= 9 * CLOCKS_PER_SEC / 10)
      state = I_LED_ON;
    break;
    
    
  }
}


void main()
{
  
  init();
  

  IO_Write(IOP_LED, 0);

  while (1)
  {
    static int first = 1;
    
    if(first){
      if(clock() >= 5000){
        first = 0;
      }
    }
  }
  
  
}
