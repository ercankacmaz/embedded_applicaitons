
#include <stdio.h>
#include <stdarg.h>

#include "system.h"
#include "io.h"
#include "uart.h"

static USART_TypeDef *_pUART[] = {
  USART1,
  USART2,
  USART3
};

struct UART_CFG {
  IO_IDX         ioRx;
  IO_IDX         ioTx;
  uint32_t       ckUart;
};

static struct UART_CFG _uCfg[] = {
  {IOP_U1RX, IOP_U1TX, RCC_APB2Periph_USART1},
  {IOP_U2RX, IOP_U2TX, RCC_APB1Periph_USART2},
  {IOP_U3RX, IOP_U3TX, RCC_APB1Periph_USART3},
};

void UART_Init(UART_IDX idx, int baud)
{
  USART_InitTypeDef _uInit;
  
  // 1) I/O uçlari yapilandirmasi
  // RX ucu input floating olmali
  IO_Init(_uCfg[idx].ioRx, IO_MODE_INPUT);
  
  // TX ucu alternate push-pull olmali
  IO_Init(_uCfg[idx].ioTx, IO_MODE_ALTERNATE);
  
  ////////////////////////////////////////////////
  // 2) UART'in clockunu aktive ediyoruz
  if (idx == UART_1)
    RCC_APB2PeriphClockCmd(_uCfg[idx].ckUart, ENABLE);
  else
    RCC_APB1PeriphClockCmd(_uCfg[idx].ckUart, ENABLE);  
  
  /////////////////////////////////////////////////
  // 3) Çevresel birimin parametereleri yapilandirilir
  //USART_StructInit(&_uInit);  // Gerekli degil
  
  _uInit.USART_BaudRate = baud;
  _uInit.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  _uInit.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  _uInit.USART_Parity = USART_Parity_No;
  _uInit.USART_StopBits = USART_StopBits_1;
  _uInit.USART_WordLength = USART_WordLength_8b;
  
  USART_Init(_pUART[idx], &_uInit);
  
  //////////////////////////////////////////////////
  // 4) Çevresel birim baslatilir
  
  USART_Cmd(_pUART[idx], ENABLE);
}


void UART_Send(UART_IDX idx, unsigned char ch)
{
  // TXE = 0 oldugu müddetçe bekle (yani Transmit Data Register dolu, gönderim için bosalmasini bekle)
  while (!USART_GetFlagStatus(_pUART[idx], USART_FLAG_TXE))
    ;
  // TXE = 1 yani Transmit Data Register bos, artik veri gönderebiliriz.
  USART_SendData(_pUART[idx], ch);
}

void UART_Send2(UART_IDX idx, unsigned char ch)
{
  // TXE = 1, Yükleme için TDR(Transmit Data Register) uygun durumda 
  USART_SendData(_pUART[idx], ch);
  
  // TC = 0 oldugu müddetçe  bekle
  // TSR(Transmit Shift Register) veri göndermeyi bitirene kadar bekle
  while(!USART_GetFlagStatus(_pUART[idx], USART_FLAG_TC))
    ;
}

// Ilgili UART portunun receive data registerinda veri var mi?
// true -> RX buffer bos degil (not empty)
// false -> Rx buffer bos (empty)
int UART_ChkRxBuf(UART_IDX idx)
{
  return USART_GetFlagStatus(_pUART[idx], USART_FLAG_RXNE);
}

// Ilgili UART porttan veri alir, bufferda veri yoksa bloke bekler
// Geri dönüs degeri 0 ise basarili, degilse hata kodu 
int UART_Recv(UART_IDX idx, unsigned char *pc)
{
  int err = UART_SUCCESS;
  // Veri hazir olana kadar bloke bekle
  // RXNE = 0 ise veri hazir degil
  while (!UART_ChkRxBuf(idx))
    ;
  
  // Veriyi çekmeden once hata kontrolü yaomaliyiz
  if (USART_GetFlagStatus(_pUART[idx], USART_FLAG_ORE))
    err = UART_ERR_OVERRUN;
  else if (USART_GetFlagStatus(_pUART[idx], USART_FLAG_NE))
    err = UART_ERR_NOISE;
  else if (USART_GetFlagStatus(_pUART[idx], USART_FLAG_FE))
    err = UART_ERR_FRAMING;
  else if (USART_GetFlagStatus(_pUART[idx], USART_FLAG_PE))
    err = UART_ERR_PARITY;
  
  *pc = (unsigned char)USART_ReceiveData(_pUART[idx]);
  
  return err;
  
}


/////////////////////////////////////////////////

void UART_putch(unsigned char c)
{
  switch (c) {
  case '\n':
    UART_Send(CON_UART, '\r');
    UART_Send(CON_UART, '\n');
    break;
    
    default:
      UART_Send(CON_UART, c);
      break; 
  }
}


int UART_puts(const char *str)
{
  int i = 0;
  while (str[i])
    UART_putch(str[i++]);
  
  return i;
}

int UART_printf(const char *fmt, ...)
{
  int size;
  
  va_list args;
  static char str[256];
  
  va_start(args, fmt);
  vsnprintf(str, 256, fmt, args);
  
  size = UART_puts(str);
  
  return size;
}

