/*
"io.h"
*/



#ifndef IO_H
#define IO_H

//CMSIS core + CMSIS device + PLIB
#include "stm32f10x.h"



typedef enum {
  IO_MODE_INPUT = GPIO_Mode_IN_FLOATING, 
  IO_MODE_OUTPUT = GPIO_Mode_Out_PP,
  IO_MODE_ALTERNATE = GPIO_Mode_AF_PP,
  IO_MODE_ANALOG = GPIO_Mode_AIN,
  
  IO_MODE_INPUT_PD = GPIO_Mode_IPD,
  IO_MODE_INPUT_PU = GPIO_Mode_IPU,
  IO_MODE_OUTPUT_OD = GPIO_Mode_Out_OD,
  IO_MODE_ALTERNATE_OD = GPIO_Mode_AF_OD,
} IO_MODE;
typedef enum {
  // LED
  IOP_LED,
  
  // Buttons
  IOP_BTN_SET,
  IOP_BTN_UP,
  IOP_BTN_DN,    // BUTTTON DOWN
  
  // UART
  IOP_U1RX,
  IOP_U1TX,
  IOP_U2RX,
  IOP_U2TX,
  IOP_U3RX,
  IOP_U3TX,
  
  // Alfanümerik LCD modül
  IOP_LCD_RS,
  IOP_LCD_E,
  IOP_LCD_DB4,
  IOP_LCD_DB5,
  IOP_LCD_DB6,
  IOP_LCD_DB7,
} IO_IDX;

typedef struct {
  GPIO_TypeDef *port;
  uint32_t pin;
} IO_PIN;


#ifdef _IOS_
IO_PIN _ios[] = {
  {GPIOC, 13},    // LED
  
  // Buttons
  {GPIOA, 0},     // Set Button
  {GPIOA, 1},     // Up Button
  {GPIOA, 2},     // Down Button
  
  // UART
  {GPIOA, 10},   // U1RX
  {GPIOA, 9},    // U1TX
  {GPIOA, 3},    // U2RX
  {GPIOA, 2},    // U2TX
  {GPIOB, 11},   // U3RX
  {GPIOB, 10},   // U3TX
  
  // Alfanümerik LCD modül
  {GPIOB, 9},   // RS
  {GPIOB, 8},   // E
  {GPIOB, 7},   // DB4
  {GPIOB, 6},   // DB5
  {GPIOB, 5},   // DB6
  {GPIOB, 4},   // DB7
  
};
#else
extern IO_PIN _ios[];
#endif

void IO_Init(IO_IDX idx, IO_MODE mode);
void IO_Write(IO_IDX idx, int val);
int IO_Read(IO_IDX idx);




#endif