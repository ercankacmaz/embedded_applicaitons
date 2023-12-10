

#include "io.h"
#include "system.h"
#include "button.h"


static BUTTON_t _bts[] = {
  {IOP_BTN_SET, 1, 0, 0},
  {IOP_BTN_UP, 1, 0, 0},
  {IOP_BTN_DN, 1, 0, 0},
};

#define N_BUTTONS       (sizeof(_bts) / sizeof(BUTTON_t))

int g_dbcMax = 50;  // Max de-bounce sayisi

// Sinyalizasyon 
volatile int g_Buttons[N_BUTTONS] = { 0 };
  
static int _btnInit = 0;  
  
  
///////////////////////////////////////////////////////////////

void BTN_Init(void)
{
  int i;

  for (i = 0; i < N_BUTTONS; ++i)
  {
    IO_Init(_bts[i].ioIdx,
            _bts[i].cState ? IO_MODE_INPUT_PU : IO_MODE_INPUT_PD);
  }
  
  _btnInit = 1;
}

static void BTN_Scan(int idx)
{
  int r;       // anlik okuma degeri
  
  r = IO_Read(_bts[idx].ioIdx);
  
  if (r != _bts[idx].cState)
  {
     // Ya tusa basildi / birakildi (durum degisti)
    // Ya da parazit siçrama
    
    if (++_bts[idx].dbc >= g_dbcMax)
    {
      // Parazit degil
      _bts[idx].cState = r;
      _bts[idx].dbc = 0;
      
      if (_bts[idx].cState == _bts[idx].aState)
      {
        // Signal
        g_Buttons[idx] = 1;
      }
    }
  }
  else 
    _bts[idx].dbc = 0;
  
} 

void BTN_ScanButtons(void)
{
  int i;
  
  if(!_btnInit)
    return;
  
  for (i = 0; i < N_BUTTONS; ++i)
    BTN_Scan(i);
}


