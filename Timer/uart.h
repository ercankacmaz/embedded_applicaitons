/*
"uart.h"
*/


#ifndef UART_H
#define UART_H

//CMSIS core + CMSIS device + PLIB
#include "stm32f10x.h"


typedef enum{
  UART_1,
  UART_2,
  UART_3,
} UART_IDX;

#define UART_SUCCESS        0
#define UART_ERR_OVERRUN    1
#define UART_ERR_NOISE      2
#define UART_ERR_FRAMING    3
#define UART_ERR_PARITY     4


void UART_Init(UART_IDX idx, int baud);
void UART_Send(UART_IDX idx, unsigned char ch);
void UART_Send2(UART_IDX idx, unsigned char ch);


int UART_ChkRxBuf(UART_IDX idx);
int UART_Recv(UART_IDX idx, unsigned char *pc);

void UART_putch(unsigned char c);
int UART_puts(const char *str);
int UART_printf(const char *fmt, ...);




#endif