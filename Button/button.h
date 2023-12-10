/*
"button.h"
*/




#ifndef BUTTON_H
#define BUTTON_H


#include "io.h"
#include "system.h"

typedef struct {
  IO_IDX      ioIdx;
  int         cState; // kompanse edilmis güncel isaret
  int         aState; // aktif durum
  int         dbc;    // de-bounce counter
} BUTTON_t;

enum {
  BTN_SET,
  BTN_UP,
  BTN_DN,
};



extern int g_dbcMax;                 // Max de-bounce sayisi
extern volatile int g_Buttons[];     // Button sayisi

void BTN_Init(void);
void BTN_ScanButtons(void);



#endif