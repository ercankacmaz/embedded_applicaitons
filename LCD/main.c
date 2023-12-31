#include <stdio.h>
#include <stdint.h>

#include "system.h"
#include "io.h"
#include "lcd.h"



void init(void)
{
  // I/O protlari baslangiÁ
  sys_ioInit();
  Sys_TickInit();
  
  // System Clock Tick
  
  // LED baslangiÁ
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
    if ( t1 - t0 >= 19 * CLOCKS_PER_SEC / 10)
      state = I_LED_ON;
    break;
    
  }
}

void Task_Print(void)
{
  static unsigned long count;
  
  printf("Sayac:%10lu", ++count);
}

void main()
{
  
  init();
  LCD_Init();
  
  //printf("Hello\n world!");

  IO_Write(IOP_LED, 0);

  while (1)
  {
    Task_LED();
    Task_Print();
    
  }
  
  
}
