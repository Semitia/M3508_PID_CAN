#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 
#include "can.h" 
#include "pid.h"

//�ĸ�mini��

 int main(void)
 {	 
	u8 key;
	u8 i=0,t=0;
	u8 cnt=0;
	u8 canbuf[8];
	u8 res;
	u8 mode=0;//0:����can; 1:������

	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
	LCD_Init();			   	//��ʼ��LCD	
	KEY_Init();				//������ʼ��		 	
   
	CAN_Mode_Init(CAN_SJW_1tq,CAN_BS2_8tq,CAN_BS1_9tq,2,CAN_Mode_LoopBack);//CAN��ʼ������ģʽ,������1M  
	
 	while(1)
	{
		//if(USART_RX_STA&0x80000000)
		//{			}
		
		if(!mode)
		{set_speed(2000);}
		
		key=KEY_Scan(0);

	 if(key==WKUP_PRES)//WK_UP���£��ı�CAN�Ĺ���ģʽ
		{	   
			mode=!mode;
		}		 
		
		/*key=Can_Receive_Msg(canbuf);
		if(key)//���յ�������
		{			
			LCD_Fill(60,270,130,310,WHITE);//���֮ǰ����ʾ
 			for(i=0;i<key;i++)
			{									    
				if(i<4)LCD_ShowxNum(60+i*32,270,canbuf[i],3,16,0X80);	//��ʾ����
				else LCD_ShowxNum(60+(i-4)*32,290,canbuf[i],3,16,0X80);	//��ʾ����
				//printf("%d ",canbuf[i]);
 			}
			printf("��е�Ƕ�:%d  ת��:%d  ʵ�ʵ���:%d  �¶�:%d",calcu(canbuf[0],canbuf[1]),calcu(canbuf[2],canbuf[3]),calcu(canbuf[4],canbuf[5]),canbuf[6]);
			printf("\r\n");
		}*/
		
		t++; 
		delay_ms(10);
		if(t==20)
		{
			LED0=!LED0;//��ʾϵͳ��������	
			t=0;
			cnt++;
			LCD_ShowxNum(60+48,170,cnt,3,16,0X80);	//��ʾ����
		}		   
	}
}



