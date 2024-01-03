/*
"timer.h"
*/


#ifndef TIMER_H
#define TIMER_H

//CMSIS core + CMSIS device + PLIB
#include "stm32f10x.h"


typedef enum{
  TIMER_1,
  TIMER_2,
  TIMER_3,
  TIMER4,
} TIMER_IDX;

extern volatile unsigned long g_T1count;

void Timer_Init(TIMER_IDX tmNo, unsigned prescale, unsigned period, unsigned repeat);
void Timer_Start(TIMER_IDX tmNo, int bEnable);
void Timer_Reset(TIMER_IDX tmNo);
void Timer_Set(TIMER_IDX tmNo, unsigned val);
void TimerIntConfig(TIMER_IDX tmNo, int priority);




#endif