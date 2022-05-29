#include "beep.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//��������������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   

//��ʼ��PB8Ϊ�����.��ʹ������ڵ�ʱ��		    
//��������ʼ��
void BEEP_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��GPIOB�˿�ʱ��
 
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;				 //BEEP-->PB.8 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //�ٶ�Ϊ50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);	 //���ݲ�����ʼ��GPIOB.8
 
 GPIO_ResetBits(GPIOB,GPIO_Pin_13);//���0���رշ��������

}



void beep_on_mode1(void)
{
	GPIO_SetBits(GPIOB,GPIO_Pin_13);//BEEP OFF
	delay_ms(600);
	GPIO_ResetBits(GPIOB,GPIO_Pin_13);//BEEP ON
}


void beep_on_mode2(void)
{
	
	int i;
	
	for(i=0; i<5; i++)
	{
	
	GPIO_SetBits(GPIOB,GPIO_Pin_13);//BEEP OFF
	delay_ms(200);
	GPIO_ResetBits(GPIOB,GPIO_Pin_13);//BEEP ON
	delay_ms(200);
	}
	
	
}
