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
  IOP_LED,
  IOP_BUTTON,
} IO_IDX;

typedef struct {
  GPIO_TypeDef *port;
  uint32_t pin;
} IO_PIN;


#ifdef _IOS_
IO_PIN _ios[] = {
  {GPIOC, 13},
  {GPIOA, 0},
};
#else
extern IO_PIN _ios[];
#endif

void IO_Init(IO_IDX idx, IO_MODE mode);
void IO_Write(IO_IDX idx, int val);
int IO_Read(IO_IDX idx);




#endif