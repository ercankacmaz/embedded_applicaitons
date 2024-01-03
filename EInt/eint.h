/*
"eint.h"
*/


#ifndef EINT_H
#define EINT_H

//CMSIS core + CMSIS device + PLIB
#include "stm32f10x.h"


typedef enum{
  I_RISING,
  I_FALLING,
  I_RISING_FALLING,
};


void EINT_Init(IO_IDX idx, int trigger, int priority);






#endif