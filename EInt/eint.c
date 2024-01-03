#include "system.h"
#include "io.h"
#include "eint.h"


static uint32_t _EXTI_Line[] = {
   EXTI_Line0,
   EXTI_Line1,
   EXTI_Line2,
   EXTI_Line3,
   EXTI_Line4,
   EXTI_Line5,
   EXTI_Line6,
   EXTI_Line7,
   EXTI_Line8,
   EXTI_Line9,
   EXTI_Line10,
   EXTI_Line11,
   EXTI_Line12,
   EXTI_Line13,
   EXTI_Line14,
   EXTI_Line15,
};



static IRQn_Type _EXTI_IRQn[] = {
  EXTI0_IRQn,
  EXTI1_IRQn,
  EXTI2_IRQn,
  EXTI3_IRQn,
  EXTI4_IRQn,
  
  EXTI9_5_IRQn,
  EXTI9_5_IRQn,
  EXTI9_5_IRQn,
  EXTI9_5_IRQn,
  EXTI9_5_IRQn,
  
  EXTI15_10_IRQn,
  EXTI15_10_IRQn,
  EXTI15_10_IRQn,
  EXTI15_10_IRQn,
  EXTI15_10_IRQn,
  EXTI15_10_IRQn,
};


static EXTITrigger_TypeDef _Trigger[] = {
  EXTI_Trigger_Rising,
  EXTI_Trigger_Falling,
  EXTI_Trigger_Rising_Falling,
};


void EINT_Init(IO_IDX idx, int trigger, int priority)
{
  EXTI_InitTypeDef eInit;
  int pin;
  uint32_t line;
  GPIO_TypeDef *port;
  uint8_t pno;
  IRQn_Type IRQn;
  
  port = _ios[idx].port;
  pin = _ios[idx].pin;
  line = _EXTI_Line[pin];
  IRQn = _EXTI_IRQn[pin]; 
  
  if (port == GPIOA)
    pno = GPIO_PortSourceGPIOA;
  else if (port == GPIOB)
    pno = GPIO_PortSourceGPIOB;
  else if (port == GPIOC)
    pno = GPIO_PortSourceGPIOC;
  
  
  // 1) AFIO saat isareti ektive edilmeli (RCC_APB2 hatti)
  //Bu saat işareti Sys_IoInit fonksiyonunda aktive ediliyor.


  // 2) EXTIn hattı ile ilgili port pin bağlantısı kurulmalı
  // Multiplexer ile ilgili uç seçilmeli 
  GPIO_EXTILineConfig(pno, pin);


  // 3) EXTI init structure başlangıç değerleri
  eInit.EXTI_Line = line;
  eInit.EXTI_Mode = EXTI_Mode_Interrupt;
  eInit.EXTI_Trigger =   _Trigger[trigger];
  eInit.EXTI_LineCmd = ENABLE;
  
  EXTI_Init(&eInit);
  
  
  // Kesme yapılandırılması
  // Çevresel tarafı (Vendor - ST)
  EXTI_ClearITPendingBit(line);
  // EXTI_ITConfig(... EXTI_Init'te yapılıyor)
  
  // ARM tarafı (NVIC)
  NVIC_SetPriority(IRQn, priority);
  NVIC_EnableIRQ(IRQn);
}

void EXTI0_IRQHandler(void)
{
  if (EXTI_GetITStatus(EXTI_Line0))  // Hangi GPIO hattına interrupt geldiğini kontrol eder
  {
    EXTI_ClearITPendingBit(EXTI_Line0);
  }
}

void EXTI1_IRQHandler(void)
{
   if (EXTI_GetITStatus(EXTI_Line1))
  {
    EXTI_ClearITPendingBit(EXTI_Line1);
  }
}

void EXTI2_IRQHandler(void)
{
   if (EXTI_GetITStatus(EXTI_Line2))
  {
    EXTI_ClearITPendingBit(EXTI_Line2);
  }
}

void EXTI3_IRQHandler(void)
{
  
}

void EXTI4_IRQHandler(void)
{
  
}

void EXTI9_5_IRQHandler(void)
{
  
}

void EXTI15_10_IRQHandler(void)
{
  
}   













