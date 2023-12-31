#include <stdio.h>
#include <stdint.h>

#include "system.h"
#include "io.h"
#include "lcd.h"
#include "uart.h"
#include "button.h"  




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
  
  // Buttons init
  BTN_Init();
  
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
  
  LCD_printf("Sayac:%10lu\r", ++count);
}

void Task_CON(void)
{
  static unsigned long count;
  
  printf("\033[3;0H" "\033[32m" "Sayac:%10lu\r", ++count);
}

void Task_Input(void)
{
   printf("\033[5;0H" "\033[31m");
   
   printf("A0 = %d\n", IO_Read(IOP_BTN_SET));
   printf("A1 = %d\n", IO_Read(IOP_BTN_UP));
   printf("A2 = %d\n", IO_Read(IOP_BTN_DN));
}

void Task_Button(void)
{
  static int iSet, iUp, iDn;
  
  if(g_Buttons[BTN_SET])
  {
    printf("\033[9;0H" "\033[33m");
    printf("SET %d", ++iSet);
    
    g_Buttons[BTN_SET] = 0;
  }
  
  if(g_Buttons[BTN_UP])
  {
    printf("\033[10;0H" "\033[33m");
    printf("UP  %d", ++iUp);
    
    g_Buttons[BTN_UP] = 0;
  }
  
  if(g_Buttons[BTN_DN])
  {
    printf("\033[11;0H" "\033[33m");
    printf("DN  %d", ++iDn);
    
    g_Buttons[BTN_DN] = 0;
  }
}

void main()
{
  // unsigned char c;
  
  // Baslangi� yapilandirmalari
  init(); 

  
  /*LCD_printf("Hello world!\n");
  UART_printf(UART_1, "Hello world\n");*/
  
  //IO_Write(IOP_LED, 0);

  printf("\033[2j");   // Ekrani temizle

  // G�rev �evrimi   
  while (1)
  {
    Task_LED();
    Task_LCD();
    Task_CON();
    Task_Input();
    Task_Button();
    
    /*if (UART_ChkRxBuf(CON_UART)){
      // loopback test
      if (UART_Recv(CON_UART, &c) == UART_SUCCESS){
        UART_Send(CON_UART, c);
      }
    }*/
    
  }
  
  
}
