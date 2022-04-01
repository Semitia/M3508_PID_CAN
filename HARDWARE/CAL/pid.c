#include "pid.h"
#include "sys.h"
#include "can.h"
#include "usart.h"

u8 key1;
u8 TX_buf[8]={0};
u8 RX_buf[8];
u8 flag;
double tem_speed;
double error;
double last_error;
double error_sum;
double d_error;
u16 current;
		
u16 calcu(u8 a,u8 b)
{
	return (a<<8)+b;
}

void show()
{
	printf("转速:%.0f  输出电流:%d  比例电流:%.0f  微分电流:%.0f  积分电流:%.0f  P:%.0f  D:%.0f  I:%.0f\r\n",
			   tem_speed,   current,      k_P*error,   k_D*d_error,   k_I*error_sum,  error, d_error, error_sum);
}

void set_speed(u16 goal_speed)
{
	key1=Can_Receive_Msg(RX_buf);
	if(key1)//接收到有数据
	{
		tem_speed=calcu(RX_buf[2],RX_buf[3]);
	}
	error=goal_speed-tem_speed;
	error_sum+=error;
	d_error=error-last_error;
	current=(k_P*error)+(k_I*error_sum)+(k_D*d_error);
	if(current>6000) {current=6000;}

	TX_buf[1]=current&0x00FF;      //LOW 8
	TX_buf[0]=current>>8;          //HIGH 8
	flag=Can_Send_Msg(TX_buf,8);
	/*if(flag) 
	{printf("Failed\r\n");}	//fail
	else 
	{printf("OK\r\n");}     //success*/
	last_error=error;
	show();
	return;
}






