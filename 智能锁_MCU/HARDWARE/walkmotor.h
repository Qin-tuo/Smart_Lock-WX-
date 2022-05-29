#ifndef _WALKMOTOR_H
#define _WALKMOTOR_H
#include "sys.h"
/********************************
A  	B  	C  		 D
D3 	D5 	D7		 XCLK
PC9 PB6 PE6 	 PA8
********************************/
#define  Aout  PBout(11) 
#define  Bout  PAout(5)
#define  Cout PAout(6)
#define  Dout  PAout(7)

void Walkmotor_Init(void);
void Walkmotor_ON(void);
void Walkmotor_OFF(void);
	
#endif
