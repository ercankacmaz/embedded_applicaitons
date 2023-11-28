

#include "system.h"
#include "io.h"


static const int GPIO_Clocks[] = 
{
  RCC_APB2Periph_GPIOA,
  RCC_APB2Periph_GPIOB,
  RCC_APB2Periph_GPIOC,
  RCC_APB2Periph_GPIOD,
  RCC_APB2Periph_GPIOE,
  RCC_APB2Periph_GPIOF,
  RCC_APB2Periph_GPIOG,
};

#define N_PORTS   (sizeof(GPIO_Clocks) / sizeof(int))

static volatile clock_t _TmTick = 0;


void sys_ioInit(void)
{
  int i;
  
  for (i = 0; i <N_PORTS; ++i)
    RCC_APB2PeriphClockCmd(GPIO_Clocks[i], ENABLE);
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
}


// Core tick timer'i uygun degerler ile baslatir.
void Sys_TickInit(void)
{
  // Core tick timer'i çalistirmak
  //Core tick timer kesmesini aktive etmek
  // SysTick_Config(uint32_t loadVal);
  // Tasma zamanu = 1 / CLOCKS_PER_SEC
  SysTick_Config(SystemCoreClock / CLOCKS_PER_SEC);
}
  
void Sys_ClockTick(void)
{
  ++_TmTick;
}

clock_t clock(void)
{
  return _TmTick;
}





