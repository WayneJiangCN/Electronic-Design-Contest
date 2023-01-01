/****************************************************/
// MSP432P401R
// 配置Keil独立空工程 (已将ti固件库打包至工程)
// Keil工程已配置开启FPU
// Bilibili：m-RNA
// E-mail:m-RNA@qq.com
// 创建日期:2021/9/28
/****************************************************/
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "sysinit.h"
#include "usart.h"
#include "delay.h"
#include "led.h"
#include "tim32.h"
#include "my_usart.h"
#include "key.h"
#include "adc.h"
#include "draw_api.h"
#include "key4x4.h"
#include "tpl0401a.h"
#include "math.h"
#define pi 3.1415926
uint16_t adcv1[500];
uint16_t adcv2[500];
uint16_t AD_store_point = 0;
uint16_t AD_sample_ok;
float pha_dif = 0;
uint8_t key_value;
char show_buf[] = " ";
uint16_t test = 2;
uint8_t flag = 2;
uint8_t three_flag = 4;
	uint8_t n=1;
	uint8_t k=0;
double xt1(double i)
{
    
    return sin(pi*2*i/200+pi/4);
}
double yt1(double i)
{
    
    return sin(n*pi*2*i/200);
}
int j=0;
int main(void)
{

	SysInit(); // 第3讲 时钟配置
	LED_Init();
	Fre_channel3();
	uart_init(115200); // 第7讲 串口配置
	delay_init();	   // 第4讲 滴答延时
	KEY_Init(1);
	usart2_init();
	KEY4x4_Init();
	TQL0401A_Init();
	/*开始填充初始化代码*/
	// x9c104s_init();
	//		add_R(2);
	MAP_FPU_enableModule();

	MAP_FPU_enableLazyStacking();
	InitGraph();
	delay_ms(200);
	ClearScreen(); //清屏
	/*停止填 充初始化代码*/
	adc_init1();
	printf("Hello,MSP432!\r\n");
	uint8_t gengxing =0;
	uint8_t t=0;
	// MAP_Interrupt_enableMaster(); // 开启总中断
	TQL0401A_OUT(2);
	while (1)
	{
		
		key_value = KEY4x4_Scan(0);

		if (key_value == 13)
			flag = 0; //单倍
		if (key_value == 14)
			flag = 1; //多倍
		if (flag == 0)
		{
			DrawString(10, 0, "mode: one_Fre");
			channelx();		//单倍
			Fre_channel3(); // 1倍频
			n=1;
			if (key_value == 5)
			{
				TQL0401A_OUT(0);

				DrawString(10, 20, "Amplitude: 2Vp-p"); //清屏 //改电位计的值
				UpdateScreen();
			}
			if (key_value == 6)

			{
				TQL0401A_OUT(1);
				DrawString(10, 20, "Amplitude: 3Vp-p"); //清屏 //改电位计的值
				UpdateScreen();
			}
			if (key_value == 7)

			{
				TQL0401A_OUT(2);
				DrawString(10, 20, "Amplitude: 4Vp-p"); //清屏 //改电位计的值
				UpdateScreen();
			}
			if (key_value == 15) //测相位差
			{
			
				printf("Fre_channel0\r\n");
				
				DrawString(10, 30, "phase_difference=");
				UpdateScreen();
			}
		}
		if (flag == 1)
		{
			channely(); //多倍

			if (key_value == 9)
			{
				n=2;
				three_flag = 1;
				Fre_channel0();
				ClearScreen(); //清屏
				two_Fre();
				DrawString(10, 0, "mode: two_Fre");
				UpdateScreen();
			}
			if (key_value == 10)
			{
				n=3;
				three_flag = 2;
				Fre_channel1();
				ClearScreen(); //清屏
				three_Fre();
				DrawString(10, 0, "mode: three_Fre");
				UpdateScreen();
			}
			if (key_value == 11)
			{
				n=4;
				three_flag = 3;
				Fre_channel2();
				ClearScreen(); //清屏
				four_Fre();
				DrawString(10, 0, "mode: four_Fre");
				UpdateScreen();
			}
			if (key_value == 12)
			{
				n=5;
				three_flag = 4;
				Fre_channel2();
				ClearScreen(); //清屏
				five_Fre();
				DrawString(10, 0, "mode: five_Fre");
				UpdateScreen();
			}
			if (three_flag == 1)
			{
				if (key_value == 5)

				{
					TQL0401A_OUT(3);
					DrawString(10, 20, "Amplitude: 2Vp-p"); //清屏 //改电位计的值
					UpdateScreen();
				}
				if (key_value == 6)

				{
					TQL0401A_OUT(4);
					DrawString(10, 20, "Amplitude: 3Vp-p"); //清屏 //改电位计的值
					UpdateScreen();
				}
				if (key_value == 7)

				{
					TQL0401A_OUT(8);
					DrawString(10, 20, "Amplitude: 4Vp-p"); //清屏 //改电位计的值
					UpdateScreen();
				}
			}
			if (three_flag == 2)
			{
				if (key_value == 5)

				{
					TQL0401A_OUT(6);
					DrawString(10, 20, "Amplitude: 2Vp-p"); //清屏 //改电位计的值
					UpdateScreen();
				}
				if (key_value == 6)

				{
					TQL0401A_OUT(7);
					DrawString(10, 20, "Amplitude: 3Vp-p"); //清屏 //改电位计的值
					UpdateScreen();
				}
				if (key_value == 7)

				{
					TQL0401A_OUT(8);
					DrawString(10, 20, "Amplitude: 4Vp-p"); //清屏 //改电位计的值
					UpdateScreen();
				}
			}
			if (three_flag == 3)
			{
				if (key_value == 5)

				{
					TQL0401A_OUT(9);
					DrawString(10, 20, "Amplitude: 2Vp-p"); //清屏 //改电位计的值
					UpdateScreen();
				}
				if (key_value == 6)

				{
					TQL0401A_OUT(10);
					DrawString(10, 20, "Amplitude: 3Vp-p"); //清屏 //改电位计的值
					UpdateScreen();
				}
				if (key_value == 7)

				{
					TQL0401A_OUT(11);
					DrawString(10, 20, "Amplitude: 4Vp-p"); //清屏 //改电位计的值
					UpdateScreen();
				}
			}
			if (three_flag == 4)
			{
				if (key_value == 5)

				{
					TQL0401A_OUT(12);
					DrawString(10, 20, "Amplitude: 2Vp-p"); //清屏 //改电位计的值
					UpdateScreen();
				}
				if (key_value == 6)

				{
					TQL0401A_OUT(13);
					DrawString(10, 20, "Amplitude: 3Vp-p"); //清屏 //改电位计的值
					UpdateScreen();
				}
				if (key_value == 7)

				{
					TQL0401A_OUT(14);
					DrawString(10, 20, "Amplitude: 4Vp-p"); //清屏 //改电位计的值
					UpdateScreen();
				}
			}
		}
		if (key_value == 16) //绘图
			gengxing =1;
			if(gengxing ==1)
			if (AD_sample_ok == 1)
			{
				ClearScreen(); //清屏
				MAP_Timer_A_stopTimer(TIMER_A0_BASE);
				printf("sucess\r\n");
				for (int i = 0; i < 100; i++)
				{

				SetPointBuffer(adcv1[i] * 160.0f / 16384 + 10, adcv2[i] * 80.0f / 16384 + 20, GetDrawColor()); //画点
					
					//				printf("adcv1=%f\r\n",adcv1[i]*3.3f/16384);
					//			printf("adcv2=%f\r\n",adcv2[i]*3.3f/16384);
					UpdateScreen();
				}	
				
//						 		     for(double i=0;i<400;i+=0.5)
//    {
////		 if(j%3==1&&j<900)
////		 	SetPointBuffer(adcv1[j] * 150.0f / 16384 + 20, adcv2[j] * 120.0f / 16384 + 10, GetDrawColor()); //画点
//////		 printf("x1=%.3fy1=%.3f\r\n",15*xt1(i)+40,30*yt1(i)+32);
//////		 printf("%f\r\n",i);
////		 j++;
//       SetPointBuffer((45*xt1(i)+50),(30*yt1(i)+30),GetDrawColor());//画点 
//		UpdateScreen();
//		 
//    }
				MAP_Timer_A_startCounter(TIMER_A0_BASE, TIMER_A_UP_MODE);
				AD_sample_ok = 0;
				j=0;
				if(k>5)
				{
					k=0;
					gengxing=0;
				}
				k++;
			
			}
			
	
			
	}
}

/*
	if (key_value == 1)
		{
			ClearScreen(); //清屏
			SetFontSize(1);
			// DrawString(0, 0, "pha_dif:");
			sprintf(show_buf, "pha_dif:%.3f", pha_dif);
			DrawString(10, 0, show_buf);

			UpdateScreen();
		}
		if (key_value == 2)
			if (AD_sample_ok == 1)
			{
				ClearScreen(); //清屏
				MAP_Timer_A_stopTimer(TIMER_A0_BASE);
				printf("sucess\r\n");
				for (int i = 0; i < 400; i++)
				{

					SetPointBuffer(adcv1[i] * 60.0f / 16384 + 20, adcv2[i] * 60.0f / 16384 + 20, GetDrawColor()); //画点
					UpdateScreen();
					//				printf("adcv1=%f\r\n",adcv1[i]*3.3f/16384);
					//			printf("adcv2=%f\r\n",adcv2[i]*3.3f/16384);
				}
				MAP_Timer_A_startCounter(TIMER_A0_BASE, TIMER_A_UP_MODE);
				AD_sample_ok = 0;
			}
		if (key_value == 5)
		{
			ClearScreen(); //清屏
			Fre_channel0();
			printf("Fre_channel0\r\n");
			DrawString(10, 0, "mode: 3*Fre,2Vp-p");
			UpdateScreen();
		}
		if (key_value == 6)
		{
			ClearScreen(); //清屏
			Fre_channel1();
			printf("Fre_channel1\r\n");
			UpdateScreen();
		}
		if (key_value == 7)
		{
			ClearScreen(); //清屏
			Fre_channel2();
			printf("Fre_channel2\r\n");
			UpdateScreen();
		}
		if (key_value == 8)
		{
			ClearScreen(); //清屏
			Fre_channel3();
			printf("Fre_channel3\r\n");
			UpdateScreen();
		}
		if (key_value == 9)
		{
			ClearScreen(); //清屏
			channel0();
			printf("channel0\r\n");
			UpdateScreen();
		}
		if (key_value == 10)
		{
			ClearScreen(); //清屏
			channel3();
			printf("channel1\r\n");
			UpdateScreen();
		*/