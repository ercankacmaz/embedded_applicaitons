#include <stdio.h>
#include <stdarg.h>

#include "lcd.h"
#include "system.h"
#include "io.h"



// Paralel 4-bit haberlesme ile bir adim (4-bit)
// veri gönderilir. Veri komut ya da karakter kodu olabilir.
// Gönderilecek deger: Parametrenin low 4-biti
static void LCD_SendDataL(unsigned char c)
{
  // Senkron 4-bit paralel haberlesme
  
  // 1) Data setup (verinin hazirlnamasi)
  IO_Write(IOP_LCD_DB4, (c & 1) != 0);
  IO_Write(IOP_LCD_DB5, (c & 2) != 0);
  IO_Write(IOP_LCD_DB6, (c & 4) != 0);
  IO_Write(IOP_LCD_DB7, (c & 8) != 0);
  // Data setup hold time
  // DelayUS(1);
  
  // 2)Clock generation (verinin onaylanmasi)
  IO_Write(IOP_LCD_E, 1);
  DelayUS(1);   // Clock high time
  IO_Write(IOP_LCD_E, 0);
  DelayUS(100);   // Clock low time + process time  
  
}

void LCD_SendCmdL(unsigned char c)
{
  IO_Write(IOP_LCD_RS, 0);   // Komut modu
  
  LCD_SendDataL(c);
}


// LCD modüle 8-bit veri gönderir
void LCD_SendData(unsigned char c)
{
  LCD_SendDataL(c >> 4);   // high 4-bit
  LCD_SendDataL(c);        // low 4-bit
}

// LCD modüle 8-bit komut gönderir
void LCD_SendCmd(unsigned char c)
{
  IO_Write(IOP_LCD_RS, 0);   // Komut modu
  
  LCD_SendData(c);   // 8-bit data
  
  DelayUS(100);
}

void LCD_ClearDisplay(void)
{
  LCD_SendCmd(0x01);
  
  DelayMS(2);
}

void LCD_Control(unsigned char ctl)
{
  ctl &= 7;    //0000 0111

  LCD_SendCmd(0x08 | ctl);  
}

// LCD modüle 8-bit karakter kodu gönderir
void LCD_PutChar(unsigned char c)
{
  IO_Write(IOP_LCD_RS, 1);   // Data modu
  
  LCD_SendData(c);   // 8-bit data
}

void LCD_Shift(unsigned char rl)
{
  rl &= 1;   // 0000 0001
  LCD_SendCmd(0x18 | (rl << 2));
  
}

void LCD_SetCursor(unsigned char pos)
{
  pos &= 0x7F;
  LCD_SendCmd(0x80 | pos);
}


// LCD modülü 4-bit ara yüz ve diger uygun
// parametrelerle baslatir
void LCD_Init(void)
{
  IO_Write(IOP_LCD_RS, 0);
  IO_Write(IOP_LCD_E, 0);
  IO_Write(IOP_LCD_DB4, 0);
  IO_Write(IOP_LCD_DB5, 0);
  IO_Write(IOP_LCD_DB6, 0);
  IO_Write(IOP_LCD_DB7, 0);
  
  IO_Init(IOP_LCD_RS, IO_MODE_OUTPUT);
  IO_Init(IOP_LCD_E, IO_MODE_OUTPUT);
  IO_Init(IOP_LCD_DB4, IO_MODE_OUTPUT);
  IO_Init(IOP_LCD_DB5, IO_MODE_OUTPUT);
  IO_Init(IOP_LCD_DB6, IO_MODE_OUTPUT);
  IO_Init(IOP_LCD_DB7, IO_MODE_OUTPUT);
  
  DelayMS(40);
  
  LCD_SendDataL(0x03);
  DelayMS(5);
  
  LCD_SendDataL(0x03);
  
  LCD_SendCmd(0x32);
  LCD_SendCmd(0x28);  // N = 1, F = 0 (000010 00NF**)
  
  //LCD_SendCmd(0x08);  // Display on/off control
  LCD_Control(LCD_DISPLAY_OFF);
  
 // LCD_SendCmd(0x01);  // Display clear
  LCD_ClearDisplay();
  
  LCD_SendCmd(0x06);  // 
  
  LCD_Control(LCD_DISPLAY_ON);
  
  
}



/////////////////////////////////////////////////////////////////

void LCD_putch(unsigned char c)
{
  switch (c)
  {
  case '\r':
    LCD_SetCursor(0);
    break;
  case '\n':
    LCD_SetCursor(0x40);
    break;
  case '\f':
    LCD_ClearDisplay();
    break;
  default:
    LCD_PutChar(c);    
    break;
  }
}

int LCD_puts(const char *str)
{
  int i = 0;
  while (str[i])
    LCD_putch(str[i++]);
  
  return i;
}

int LCD_printf(const char *fmt, ...)
{
  int size;
  
  va_list args;
  static char str[256];
  
  va_start(args, fmt);
  vsnprintf(str, 256, fmt, args);
  
  size = LCD_puts(str);
  
  return size;
}


