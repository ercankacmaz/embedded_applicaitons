
#define _IOS_
#include "io.h"





void IO_Init(IO_IDX idx, IO_MODE mode)
{
  GPIO_InitTypeDef ioInit;
  
  ioInit.GPIO_Pin = (1<<_ios[idx].pin);
  ioInit.GPIO_Speed = GPIO_Speed_50MHz;
  ioInit.GPIO_Mode = (GPIOMode_TypeDef)mode;
  
  GPIO_Init(_ios[idx].port, &ioInit);
}

void IO_Write(IO_IDX idx, int val)
{
  uint32_t mask;
  GPIO_TypeDef *GPIOx;
  
  mask = (1 << _ios[idx].pin);
  GPIOx = _ios[idx].port;
  
  if(val)
    GPIOx->BSRR = mask;
  else
    GPIOx->BSRR = (mask << 16);
}

int IO_Read(IO_IDX idx)
{
  uint32_t mask;
  GPIO_TypeDef *GPIOx;
  GPIOx = _ios[idx].port;

  mask = (1 << _ios[idx].pin);
  
  return (GPIOx->IDR & mask) != 0;
}