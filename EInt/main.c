#include <stdio.h>
#include <stdint.h>

#include "system.h"
#include "io.h"
#include "lcd.h"
#include "uart.h"
#include "timer.h"
#include "eint.h"



void init(void)
{
  // I/O protlari baslangi�
  sys_ioInit();
  // System Clock Tick
  Sys_TickInit();
  
  // Konsol init
  Sys_ConsoleInit();
  
  
  // LCD init
  LCD_Init();
  
  // LED baslangi�
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

void Task_LCD(void)
{
  static unsigned long count;
  
  LCD_printf("Sayac:%10lu", ++count);
}

void Task_CON(void)
{
  //printf("\033[0;0H" "\033[33m" "T1: %10lu\r", g_T1count);
}



void main()
{ 
  // Başlangıç yapılandırmaları
  init(); 

  
  /*LCD_printf("Hello world!\n");
  UART_printf(UART_1, "Hello world\n");*/
  
 /* Timer_Init(TIMER_1, 36000, 2000, 1);
  Timer_Start(TIMER_1, 1);

  TimerIntConfig(TIMER_1, 3);*/
  
  IO_Init(IOP_BTN_SET, IO_MODE_INPUT_PU);
  IO_Init(IOP_BTN_UP, IO_MODE_INPUT_PU);
  IO_Init(IOP_BTN_DN, IO_MODE_INPUT_PU);
  
  EINT_Init(IOP_BTN_SET, I_FALLING, 3);
  EINT_Init(IOP_BTN_UP, I_FALLING, 5);
  EINT_Init(IOP_BTN_DN, I_FALLING, 2);

  // Görev çevrimi
  while (1)
  {
    Task_LED();
   // Task_LCD();
    Task_CON(); 
  }
  
  
}
