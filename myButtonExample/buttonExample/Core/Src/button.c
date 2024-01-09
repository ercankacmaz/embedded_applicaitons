#include "main.h"
#include "tim.h"
#include "gpio.h"
#include "button.h"

#include <stdbool.h>



#define _io     static
#define _ioo    static volatile

#define NUMBER_OF_BUTTONS       3
#define DEBOUNCE_TIME           50

extern TIM_HandleTypeDef htim3;


typedef struct {
  bool intFlag;
  bool pressed;
  uint16_t cnt;
  uint16_t pressedCnt;
  GPIO_TypeDef *GPIOx;
  uint16_t GPIO_Pin;
} Button;


_io Button button[NUMBER_OF_BUTTONS] = {
  {false, false, 0, 0, GPIOA, GPIO_PIN_0},
  {false, false, 0, 0, GPIOA, GPIO_PIN_1},
  {false, false, 0, 0, GPIOA, GPIO_PIN_3},
};

uint16_t cnt1 = 0;

void setBtnData(uint16_t *data)
{
  for (int i = 0; i < NUMBER_OF_BUTTONS; ++i)
  {
    if(button[i].pressed)
    {
      
      button[i].pressedCnt = HAL_GetTick();
      if(HAL_GPIO_ReadPin(button[i].GPIOx, button[i].GPIO_Pin) == GPIO_PIN_SET)
      {
        ++cnt1;
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
        ++data[i];
        button[i].pressed = false;
      }
    }
  }
}




void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  for (int i = 0; i < NUMBER_OF_BUTTONS; ++i)
  {
    if (GPIO_Pin == button[i].GPIO_Pin) {
        if (HAL_GPIO_ReadPin(button[i].GPIOx, button[1].GPIO_Pin) == GPIO_PIN_RESET)
          button[i].intFlag = true;
        else
          button[1].intFlag = false;
    }
  }
}




void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  for (int i = 0; i < NUMBER_OF_BUTTONS; ++i)
  {
    if (htim == &htim3) 
    {
          if (button[i].intFlag) 
          {
              if (++button[i].cnt >= DEBOUNCE_TIME)
              {
                button[i].pressed = true;
                button[i].cnt = 0;
                button[i].intFlag = false;
              }
          } 
          else 
          {
              button[i].cnt = 0;
          }
    }
  }
}