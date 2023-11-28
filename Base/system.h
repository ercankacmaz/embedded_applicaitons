/*
"system.h"
*/



#ifndef SYSTEM_H
#define SYSTEM_H

#define CLOCKS_PER_SEC    1000

typedef unsigned long clock_t;

#define CLOCK_FREQ    72000000
#define INSt_FREQ     (CLOCK_FREQ * 4 / 5)

#define MS_CYCLES     (INSt_FREQ / 1000)
#define US_CYCLES     10 * (INST_FREQ / 100000)

#define DelayUS(us)   __delay((us) * US_CYCLES)
#define DelayMS(ms)   __delay((ms) * MS_CYCLES)

void __delay(unsigned long ncy); 


void sys_ioInit(void);
void Sys_TickInit(void);

clock_t clock(void);


#endif