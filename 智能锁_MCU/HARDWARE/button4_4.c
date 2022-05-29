#include "button4_4.h"
#include <delay.h>
#include "usart.h"
//行输出端口定义
#define X1_GPIO_PORT GPIOB
#define X2_GPIO_PORT GPIOB
#define X3_GPIO_PORT GPIOB
#define X4_GPIO_PORT GPIOB
//列输入端口定义
#define Y1_GPIO_PORT GPIOB
#define Y2_GPIO_PORT GPIOB
#define Y3_GPIO_PORT GPIOB
#define Y4_GPIO_PORT GPIOB

//行输出引脚定义
#define X1_GPIO_PIN GPIO_Pin_4
#define X2_GPIO_PIN GPIO_Pin_5
#define X3_GPIO_PIN GPIO_Pin_6
#define X4_GPIO_PIN GPIO_Pin_7

//列输入引脚定义
#define Y1_GPIO_PIN GPIO_Pin_0
#define Y2_GPIO_PIN GPIO_Pin_1
#define Y3_GPIO_PIN GPIO_Pin_14
#define Y4_GPIO_PIN GPIO_Pin_3

//行输出时钟定义
#define X1_RCC RCC_APB2Periph_GPIOB
#define X2_RCC RCC_APB2Periph_GPIOB
#define X3_RCC RCC_APB2Periph_GPIOB
#define X4_RCC RCC_APB2Periph_GPIOB

//列输入时钟定义
#define Y1_RCC RCC_APB2Periph_GPIOB
#define Y2_RCC RCC_APB2Periph_GPIOB
#define Y3_RCC RCC_APB2Periph_GPIOB
#define Y4_RCC RCC_APB2Periph_GPIOB

unsigned char Y1, Y2, Y3, Y4;
void Button4_4_Init(void) //
{
       GPIO_InitTypeDef GPIO_InitStructure;

       RCC_APB2PeriphClockCmd(X1_RCC | X2_RCC | X3_RCC | X4_RCC | Y1_RCC | Y2_RCC | Y3_RCC | Y4_RCC | RCC_APB2Periph_AFIO, ENABLE);
       GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

       /*****************************4行输出*********************************************/
       GPIO_InitStructure.GPIO_Pin = X1_GPIO_PIN;
       GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
       GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
       GPIO_Init(X1_GPIO_PORT, &GPIO_InitStructure);

       GPIO_InitStructure.GPIO_Pin = X2_GPIO_PIN;
       GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
       GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
       GPIO_Init(X2_GPIO_PORT, &GPIO_InitStructure);

       GPIO_InitStructure.GPIO_Pin = X3_GPIO_PIN;
       GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
       GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
       GPIO_Init(X3_GPIO_PORT, &GPIO_InitStructure);

       GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
       GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
       GPIO_InitStructure.GPIO_Pin = X4_GPIO_PIN;
       GPIO_Init(X4_GPIO_PORT, &GPIO_InitStructure);

       /**************************************4列输入*************************************/
       GPIO_InitStructure.GPIO_Pin = Y1_GPIO_PIN;
       GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
       GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
       GPIO_Init(Y1_GPIO_PORT, &GPIO_InitStructure);

       GPIO_InitStructure.GPIO_Pin = Y2_GPIO_PIN;
       GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
       GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
       GPIO_Init(Y2_GPIO_PORT, &GPIO_InitStructure);

       GPIO_InitStructure.GPIO_Pin = Y3_GPIO_PIN;
       GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
       GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
       GPIO_Init(Y3_GPIO_PORT, &GPIO_InitStructure);

       GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
       GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
       GPIO_InitStructure.GPIO_Pin = Y4_GPIO_PIN;
       GPIO_Init(Y4_GPIO_PORT, &GPIO_InitStructure);
}

/*********************************************************************

**********************************************************************/
int keyValue = 0; //
uchar KeyVal;
int Button4_4_Scan(void)
{
       //	GPIO_Write(KEY4_4PORT, ((KEY4_4PORT->ODR & 0xff00) | 0x000f)); //拉高

       //	if ((KEY4_4PORT->IDR & 0x00f0) == 0x0000)
       //		return -1;
       //	else
       //	{
       //		delay_ms(20);

       //		if ((KEY4_4PORT->IDR & 0x00f0) == 0x0000) //
       //			return -1;
       //	}

       //	GPIO_Write(KEY4_4PORT, (KEY4_4PORT->ODR & 0xfff0) | 0x0001); //?PA8-11??0001,?????
       //																 // printf("0x%x\r\n",KEY4_4PORT->IDR & 0x00f0);
       //	switch (KEY4_4PORT->IDR & 0x00f0)
       //	{
       //	case 0x0010:
       //		keyValue = 4;
       //		break;
       //	case 0x0020:
       //		keyValue = 3;
       //		break;
       //	case 0x0040:
       //		keyValue = 2;
       //		break;
       //	case 0x0080:
       //		keyValue = 1;
       //		break;
       //	}
       //	while ((KEY4_4PORT->IDR & 0x00f0) != 0x0000);

       //	GPIO_Write(KEY4_4PORT, (KEY4_4PORT->ODR & 0xfff0) | 0x0002); //?PA8-11??0010,?????
       //																 // printf("0x%x\r\n",KEY4_4PORT->IDR & 0x00f0);
       //	switch (KEY4_4PORT->IDR & 0x00f0)
       //	{
       //	case 0x0010:
       //		keyValue = 8;
       //		break;
       //	case 0x0020:
       //		keyValue = 7;
       //		break;
       //	case 0x0040:
       //		keyValue = 6;
       //		break;
       //	case 0x0080:
       //		keyValue = 5;
       //		break;
       //	}
       //	while ((KEY4_4PORT->IDR & 0x00f0) != 0x0000);

       //	GPIO_Write(KEY4_4PORT, (KEY4_4PORT->ODR & 0xfff0) | 0x0004); //?PA8-11??0100,?????
       //																 // printf("0x%x\r\n",KEY4_4PORT->IDR & 0x00f0);
       //	switch (KEY4_4PORT->IDR & 0x00f0)
       //	{
       //	case 0x0010:
       //		keyValue = 12;
       //		break;
       //	case 0x0020:
       //		keyValue = 11;
       //		break;
       //	case 0x0040:
       //		keyValue = 10;
       //		break;
       //	case 0x0080:
       //		keyValue = 9;
       //		break;
       //	}
       //	while ((KEY4_4PORT->IDR & 0x00f0) != 0x0000);

       //	GPIO_Write(KEY4_4PORT, (KEY4_4PORT->ODR & 0xfff0) | 0x0008); //?PA8-11??1000,?????
       //																 // printf("0x%x\r\n",KEY4_4PORT->IDR & 0x00f0);
       //	switch (KEY4_4PORT->IDR & 0x00f0)
       //	{
       //	case 0x0010:
       //		keyValue = 16;
       //		break;
       //	case 0x0020:
       //		keyValue = 15;
       //		break;
       //	case 0x0040:
       //		keyValue = 14;
       //		break;
       //	case 0x0080:
       //		keyValue = 13;
       //		break;
       //	}
       //	while ((KEY4_4PORT->IDR & 0x00f0) != 0x0000);

       //	return 17 - keyValue;

        GPIO_SetBits(X1_GPIO_PORT,X1_GPIO_PIN);  
   GPIO_SetBits(X2_GPIO_PORT,X2_GPIO_PIN);  
   GPIO_SetBits(X3_GPIO_PORT,X3_GPIO_PIN);  
   GPIO_SetBits(X4_GPIO_PORT,X4_GPIO_PIN);  


	if((GPIO_ReadInputDataBit(Y1_GPIO_PORT,Y1_GPIO_PIN)|GPIO_ReadInputDataBit(Y2_GPIO_PORT,Y2_GPIO_PIN)|GPIO_ReadInputDataBit(Y3_GPIO_PORT,Y3_GPIO_PIN)|GPIO_ReadInputDataBit(Y4_GPIO_PORT,Y4_GPIO_PIN))==0x0000)  
        return -1;   
	 else
	 {	
	    delay_ms(5);    
         if((GPIO_ReadInputDataBit(Y1_GPIO_PORT,Y1_GPIO_PIN)|GPIO_ReadInputDataBit(Y2_GPIO_PORT,Y2_GPIO_PIN)|GPIO_ReadInputDataBit(Y3_GPIO_PORT,Y3_GPIO_PIN)|GPIO_ReadInputDataBit(Y4_GPIO_PORT,Y4_GPIO_PIN))==0x0000)
	    return -1;
	 }
	 
     GPIO_ResetBits(X1_GPIO_PORT,X1_GPIO_PIN);
     GPIO_ResetBits(X2_GPIO_PORT,X2_GPIO_PIN);
     GPIO_ResetBits(X3_GPIO_PORT,X3_GPIO_PIN);
     GPIO_SetBits(X4_GPIO_PORT,X4_GPIO_PIN); 
     
    Y1=GPIO_ReadInputDataBit(Y1_GPIO_PORT,Y1_GPIO_PIN);Y2=GPIO_ReadInputDataBit(Y2_GPIO_PORT,Y2_GPIO_PIN);
    Y3=GPIO_ReadInputDataBit(Y3_GPIO_PORT,Y3_GPIO_PIN);Y4=GPIO_ReadInputDataBit(Y4_GPIO_PORT,Y4_GPIO_PIN);
     if(Y1==1&&Y2==0&&Y3==0&&Y4==0)
            KeyVal=4;
     if(Y1==0&&Y2==1&&Y3==0&&Y4==0)
            KeyVal=8;
     if(Y1==0&&Y2==0&&Y3==0&&Y4==1)
            KeyVal=16;
     if(Y1==0&&Y2==0&&Y3==1&&Y4==0)
            KeyVal=12;
    
     while(((GPIO_ReadInputDataBit(Y1_GPIO_PORT,Y1_GPIO_PIN))|(GPIO_ReadInputDataBit(Y2_GPIO_PORT,Y2_GPIO_PIN))|(GPIO_ReadInputDataBit(Y3_GPIO_PORT,Y3_GPIO_PIN))|(GPIO_ReadInputDataBit(Y4_GPIO_PORT,Y4_GPIO_PIN))) > 0);
     GPIO_SetBits(X1_GPIO_PORT,X1_GPIO_PIN);
     GPIO_ResetBits(X2_GPIO_PORT,X2_GPIO_PIN);
     GPIO_ResetBits(X3_GPIO_PORT,X3_GPIO_PIN);
     GPIO_ResetBits(X4_GPIO_PORT,X4_GPIO_PIN);
   
    Y1=GPIO_ReadInputDataBit(Y1_GPIO_PORT,Y1_GPIO_PIN);Y2=GPIO_ReadInputDataBit(Y2_GPIO_PORT,Y2_GPIO_PIN);
    Y3=GPIO_ReadInputDataBit(Y3_GPIO_PORT,Y3_GPIO_PIN);Y4=GPIO_ReadInputDataBit(Y4_GPIO_PORT,Y4_GPIO_PIN);
     if(Y1==1&&Y2==0&&Y3==0&&Y4==0)
            KeyVal=1;
     if(Y1==0&&Y2==1&&Y3==0&&Y4==0)
            KeyVal=5;
     if(Y1==0&&Y2==0&&Y3==1&&Y4==0)
            KeyVal=9;
     if(Y1==0&&Y2==0&&Y3==0&&Y4==1)
            KeyVal=13;
       
      while(((GPIO_ReadInputDataBit(Y1_GPIO_PORT,Y1_GPIO_PIN))|(GPIO_ReadInputDataBit(Y2_GPIO_PORT,Y2_GPIO_PIN))|(GPIO_ReadInputDataBit(Y3_GPIO_PORT,Y3_GPIO_PIN))|(GPIO_ReadInputDataBit(Y4_GPIO_PORT,Y4_GPIO_PIN))) > 0);
		

     GPIO_ResetBits(X1_GPIO_PORT,X1_GPIO_PIN);
     GPIO_SetBits(X2_GPIO_PORT,X2_GPIO_PIN);
     GPIO_ResetBits(X3_GPIO_PORT,X3_GPIO_PIN);
     GPIO_ResetBits(X4_GPIO_PORT,X4_GPIO_PIN);
        
     Y1=GPIO_ReadInputDataBit(Y1_GPIO_PORT,Y1_GPIO_PIN);Y2=GPIO_ReadInputDataBit(Y2_GPIO_PORT,Y2_GPIO_PIN);
     Y3=GPIO_ReadInputDataBit(Y3_GPIO_PORT,Y3_GPIO_PIN);Y4=GPIO_ReadInputDataBit(Y4_GPIO_PORT,Y4_GPIO_PIN);
     if(Y1==1&&Y2==0&&Y3==0&&Y4==0)
            KeyVal=2;
     if(Y1==0&&Y2==1&&Y3==0&&Y4==0)
            KeyVal=6;
     if(Y1==0&&Y2==0&&Y3==1&&Y4==0)
            KeyVal=10;
     if(Y1==0&&Y2==0&&Y3==0&&Y4==1)
            KeyVal=14;
    
      while(((GPIO_ReadInputDataBit(Y1_GPIO_PORT,Y1_GPIO_PIN))|(GPIO_ReadInputDataBit(Y2_GPIO_PORT,Y2_GPIO_PIN))|(GPIO_ReadInputDataBit(Y3_GPIO_PORT,Y3_GPIO_PIN))|(GPIO_ReadInputDataBit(Y4_GPIO_PORT,Y4_GPIO_PIN))) > 0);
		
     GPIO_ResetBits(X1_GPIO_PORT,X1_GPIO_PIN);
     GPIO_ResetBits(X2_GPIO_PORT,X2_GPIO_PIN);
     GPIO_SetBits(X3_GPIO_PORT,X3_GPIO_PIN);
     GPIO_ResetBits(X4_GPIO_PORT,X4_GPIO_PIN);   

     Y1=GPIO_ReadInputDataBit(Y1_GPIO_PORT,Y1_GPIO_PIN);Y2=GPIO_ReadInputDataBit(Y2_GPIO_PORT,Y2_GPIO_PIN);
     Y3=GPIO_ReadInputDataBit(Y3_GPIO_PORT,Y3_GPIO_PIN);Y4=GPIO_ReadInputDataBit(Y4_GPIO_PORT,Y4_GPIO_PIN);
     if(Y1==1&&Y2==0&&Y3==0&&Y4==0)
            KeyVal=3;
     if(Y1==0&&Y2==1&&Y3==0&&Y4==0)
            KeyVal=7;
     if(Y1==0&&Y2==0&&Y3==1&&Y4==0)
            KeyVal=11;
     if(Y1==0&&Y2==0&&Y3==0&&Y4==1)
            KeyVal=15;

       while(((GPIO_ReadInputDataBit(Y1_GPIO_PORT,Y1_GPIO_PIN))|(GPIO_ReadInputDataBit(Y2_GPIO_PORT,Y2_GPIO_PIN))|(GPIO_ReadInputDataBit(Y3_GPIO_PORT,Y3_GPIO_PIN))|(GPIO_ReadInputDataBit(Y4_GPIO_PORT,Y4_GPIO_PIN))) > 0);
	  
		return KeyVal;
}
