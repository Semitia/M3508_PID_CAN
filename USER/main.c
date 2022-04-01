#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 
#include "can.h" 
#include "pid.h"

//改给mini了

 int main(void)
 {	 
	u8 key;
	u8 i=0,t=0;
	u8 cnt=0;
	u8 canbuf[8];
	u8 res;
	u8 mode=0;//0:发送can; 1:不发送

	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//串口初始化为115200
	LED_Init();		  		//初始化与LED连接的硬件接口
	LCD_Init();			   	//初始化LCD	
	KEY_Init();				//按键初始化		 	
   
	CAN_Mode_Init(CAN_SJW_1tq,CAN_BS2_8tq,CAN_BS1_9tq,2,CAN_Mode_LoopBack);//CAN初始化环回模式,波特率1M  
	
 	while(1)
	{
		//if(USART_RX_STA&0x80000000)
		//{			}
		
		if(!mode)
		{set_speed(2000);}
		
		key=KEY_Scan(0);

	 if(key==WKUP_PRES)//WK_UP按下，改变CAN的工作模式
		{	   
			mode=!mode;
		}		 
		
		/*key=Can_Receive_Msg(canbuf);
		if(key)//接收到有数据
		{			
			LCD_Fill(60,270,130,310,WHITE);//清除之前的显示
 			for(i=0;i<key;i++)
			{									    
				if(i<4)LCD_ShowxNum(60+i*32,270,canbuf[i],3,16,0X80);	//显示数据
				else LCD_ShowxNum(60+(i-4)*32,290,canbuf[i],3,16,0X80);	//显示数据
				//printf("%d ",canbuf[i]);
 			}
			printf("机械角度:%d  转速:%d  实际电流:%d  温度:%d",calcu(canbuf[0],canbuf[1]),calcu(canbuf[2],canbuf[3]),calcu(canbuf[4],canbuf[5]),canbuf[6]);
			printf("\r\n");
		}*/
		
		t++; 
		delay_ms(10);
		if(t==20)
		{
			LED0=!LED0;//提示系统正在运行	
			t=0;
			cnt++;
			LCD_ShowxNum(60+48,170,cnt,3,16,0X80);	//显示数据
		}		   
	}
}



