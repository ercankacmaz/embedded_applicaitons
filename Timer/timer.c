




#include "system.h"
#include "io.h"
#include "timer.h"


static TIM_TypeDef *_TimTab[] = {
    TIM1, TIM2, TIM3, TIM4,
};

static uint32_t _TimRccTab[] = {
    RCC_APB2Periph_TIM1,
    RCC_APB1Periph_TIM2,
    RCC_APB1Periph_TIM3,
    RCC_APB1Periph_TIM4,
};

static IRQn_Type _TimIrqTab[] = {
    TIM1_UP_IRQn,
    TIM2_IRQn,
    TIM3_IRQn,
    TIM4_IRQn,
};

// Timer birimini verilen parametler ile yapılandırır
// Timer birimi başlatılmaz
void Timer_Init(TIMER_IDX tmNo, unsigned prescale, unsigned period, unsigned repeat)
{
    TIM_TimeBaseInitTypeDef tmInit;

    // 1) Çevresel birim için clock sağlıyoruz
    if (tmNo == TIMER_1){
        RCC_APB2PeriphClockCmd(_TimRccTab[tmNo], ENABLE);
    }
    else {
        RCC_APB1PeriphClockCmd(_TimRccTab[tmNo], ENABLE);
    }

    // 2) Çevresel birimin parametreleri yapılandırılır
    tmInit.TIM_ClockDivision = TIM_CKD_DIV1;      // etkisiz
    tmInit.TIM_CounterMode = TIM_CounterMode_Up;
    tmInit.TIM_Period = period - 1;               // timerın hangi periodlar ile sıfırlanacağını belirler
    tmInit.TIM_Prescaler = prescale - 1;          // timerın her bir adımın ne kadar uzunlukta olacağını ayarlar
    tmInit.TIM_RepetitionCounter = repeat - 1;

    TIM_TimeBaseInit(_TimTab[tmNo], &tmInit);
    
    Timer_Reset(tmNo);
}


// Timer birimini çalıştırır ya da durdurur
void Timer_Start(TIMER_IDX tmNo, int bEnable)
{
    TIM_Cmd(_TimTab[tmNo], bEnable ? ENABLE : DISABLE);
}

// Timer birimini resetler
void Timer_Reset(TIMER_IDX tmNo)
{
    TIM_SetCounter(_TimTab[tmNo], 0);
}

void Timer_Set(TIMER_IDX tmNo, unsigned val)
{
    TIM_SetCounter(_TimTab[tmNo], val);
}

// priority 0 - 15 arasındadır
// 0 en yüksek önceliği belirtir
void TimerIntConfig(TIMER_IDX tmNo, int priority)
{
    // 1) Çevresel birim kesme ayarları E = 1
    // Geçmiş olaylardan etkilenmemesi için 
    // Pending statüsünü silmeliyiz
    TIM_ClearITPendingBit(_TimTab[tmNo], TIM_IT_Update);  // F = 0
    TIM_ITConfig(_TimTab[tmNo], TIM_IT_Update, ENABLE);   // E =  

    // 2) Çekirdek NVIC kesme ayarları
    // a) Öncelik ayarı
    NVIC_SetPriority(_TimIrqTab[tmNo], priority);

    // b) Kesme izni E = 1
    NVIC_EnableIRQ(_TimIrqTab[tmNo]);
}

////////////////////////////////////////////////////////////////////////////////


volatile unsigned long g_T1count;

void TIM1_UP_IRQHandler(void)
{
    // Aktif: İşleniyor
    if (TIM_GetITStatus(TIM1, TIM_IT_Update) == SET)
    {
            if (TIM_GetITStatus(TIM1, TIM_IT_Update) == SET)
            {
                ++g_T1count;
            }
    }

    TIM_ClearITPendingBit(TIM1, TIM_IT_Update);  // F = 0

}

void TIM2_IRQHandler(void)
{

}

void TIM3_IRQHandler(void)
{

}

void TIM4_IRQHandler(void)
{

}



