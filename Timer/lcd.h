/*
"lcd.h"
*/



#ifndef LCD_H
#define LCD_H

#define LCD_DISPLAY_ON     0x04
#define LCD_CURSOR_ON      0X02
#define LCD_CURSOR_BLINK   0X01
#define LCD_DISPLAY_OFF    0X00

#define LCD_SHIFT_LEFT     0
#define LCD_SHIFT_RIGHT    1

void LCD_Init(void);
void LCD_PutChar(unsigned char c);
void LCD_SendCmd(unsigned char c);
void LCD_ClearDisplay(void);
void LCD_Control(unsigned char ctl);
void LCD_Shift(unsigned char rl);
void LCD_SetCursor(unsigned char pos);
int LCD_puts(const char *str);
void LCD_putch(unsigned char c);
int LCD_printf(const char *fmt, ...);

#endif