#ifndef __PID_H
#define __PID_H
#include "sys.h"
#include "stdlib.h"


#define k_P 2.3
#define k_I 0.01
#define k_D 0.6
extern u16 calcu(u8 a,u8 b);
extern void show();
#endif

