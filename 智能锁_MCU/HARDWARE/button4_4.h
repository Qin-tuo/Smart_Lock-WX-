#ifndef _BUTTON_H 
#define _BUTTON_H
#include <sys.h>



#define KEY4_4PORT GPIOB
#define uint unsigned int 
#define uchar unsigned char
	
void Button4_4_Init(void);
int Button4_4_Scan(void);



#endif

