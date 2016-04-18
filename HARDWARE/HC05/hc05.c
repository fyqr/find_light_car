#include "delay.h" 			 
#include "usart.h" 			 
#include "usart3.h" 			 
#include "hc05.h" 
#include "led.h" 
#include "string.h"	 
#include "math.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//ATK-HC05����ģ����������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2014/10/26
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
//********************************************************************************
//���޸���Ϣ							  
////////////////////////////////////////////////////////////////////////////////// 	   

//��ʼ��ATK-HC05ģ��
//����ֵ:0,�ɹ�;1,ʧ��.
u8 HC05_Init(void)
{
	u8 retry=10,t;	  		 
	u8 temp=1;
	RCC->AHB1ENR|=1<<2;//ʹ��PORTCʱ�� 
	RCC->AHB1ENR|=1<<5;//ʹ��PORTFʱ�� 
	GPIO_Set(GPIOC,PIN0,GPIO_MODE_IN,0,0,GPIO_PUPD_PU); //PC0 ���� ����
	GPIO_Set(GPIOF,PIN3,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU); //PF6 ��� �ߵ�ƽ
 	usart3_init(42,9600);//��ʼ������3Ϊ:9600,������.
	while(retry--)
	{
		HC05_KEY=1;					//KEY�ø�,����ATģʽ
		delay_ms(10);
		u3_printf("AT\r\n");		//����AT����ָ��
		HC05_KEY=0;					//KEY����,�˳�ATģʽ
	}		    
	if(retry==0)temp=1;	//���ʧ��
	return temp;	 
}	 









