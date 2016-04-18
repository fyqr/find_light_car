#include "sys.h"
#include "delay.h"  
#include "usart.h"  
#include "led.h"
#include "lcd.h"
#include "usmart.h"		
#include "hc05.h" 	 
#include "usart3.h" 	
#include "key.h" 	 
#include "string.h"	 
#include "motor.h"
#include "adc.h"
//ALIENTEK̽����STM32F407��������չʵ��1
//ATK-HC05��������ģ��ʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾ 
 
extern u32 global_time_cnt;
extern u8 USART3_RX_BYTE;

int main(void)
{	 
	u8 last_state = 0xff;
	u16 adc4;
	u16 adc5;
	Stm32_Clock_Init(336,8,2,7);//����ʱ��,168Mhz 
	delay_init(168);			//��ʱ��ʼ��  
	uart_init(84,115200);		//��ʼ�����ڲ�����Ϊ115200 
	usmart_dev.init(84); 		//��ʼ��USMART		
	KEY_Init();					//��ʼ������
	LCD_Init();		 			//��ʼ��LCD
	Adc_Init();         //��ʼ��ADC
	usmart_dev.init(72); 		//��ʼ��USMART 	  
	POINT_COLOR=RED;
	delay_ms(1000);			//�ȴ�����ģ���ϵ��ȶ�
	
	if(HC05_Init()) 		//��ʼ��ATK-HC05ģ��  
	{
		LCD_ShowString(30,90,200,16,16,"ATK-HC05 Error!"); 
		delay_ms(500);
		LCD_ShowString(30,90,200,16,16,"Please Check!!!"); 
		delay_ms(100);
	}
	
	POINT_COLOR=BLUE;
	delay_ms(100);
	pwm_init();
	delay_ms(100);
	
	while(1)
	{
		adc4=Get_Adc_Average(4,20);//adc4���ұߵĴ�����
		adc5=Get_Adc_Average(5,20);//adc5����ߵĴ�����
		
		if(adc4<=0x400||adc5<=0x400)
		{
      car_stop();
      continue;
		}
		else if(adc4>=0xdd0 && adc5>=0xdd0)
		{
			car_right();
		}
		else if(adc4>adc5&&adc4-adc5<0x08f||adc5>adc4&&adc5-adc4<0x8f)
		{
			 car_forward();
		}
		
      else if(adc4<adc5)//�ұ���,��߰�
		{
        car_right();
		}
      else     //��������ұ߰�
		{ 
        car_left();
			
			
		}
     
	}	

	/*while(1)
	{
		switch(KEY1<<2 | KEY0<<1 | KEY2)
		{
			case 5: car_forward(); last_state = 5; break;
			case 4: car_right(); last_state = 4; break;
			case 6: car_right(); last_state = 6; break;
			case 1: car_left(); last_state = 1; break;
			case 3: car_left(); last_state = 3; break;
			case 7: {
				switch(last_state){
					case 4: 
					case 6: break;
					case 1:
					case 3: break;
					default: break;
						
				}
				break;
			}
			case 0: break;
			default: break;
		}
	}

	while(1) 
	{				
		switch(USART3_RX_BYTE)
		{
			//up, forward
			case 'w': car_forward(); break;
			//down, backward
			case 's': car_backward(); break;
			//left, turn left
			case 'a': car_left(); break;
			//right, turn right
			case 'd': car_right(); break;
			//default mode
			case 't': car_stop(); break;
			default: break;
		}
	}											    
*/
}
















