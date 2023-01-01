/*
 * led.c
 *
 *  Created on: 2020年9月10日
 *      Author: 60495
 */
#include "led.h"

void LED_Init(void)
{
//    GPIO_setAsOutputPin(GPIO_PORT_P10, GPIO_PIN3);
//    GPIO_setAsOutputPin(GPIO_PORT_P10, GPIO_PIN0);
//
//    GPIO_setOutputLowOnPin(GPIO_PORT_P10, GPIO_PIN3);
//    GPIO_setOutputLowOnPin(GPIO_PORT_P10, GPIO_PIN0);  //初始化拉低
	 GPIO_setAsOutputPin(GPIO_PORT_P8, GPIO_PIN2);	//控制
	 GPIO_setAsOutputPin(GPIO_PORT_P8, GPIO_PIN5| GPIO_PIN6); //滤波
	 GPIO_setAsOutputPin(GPIO_PORT_P8, GPIO_PIN3| GPIO_PIN7); //倍频

	 GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN2);  //初始化拉高
    GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN5| GPIO_PIN6);  //初始化拉高
	 GPIO_setOutputHighOnPin(GPIO_PORT_P8,  GPIO_PIN3| GPIO_PIN7);  //初始化拉高

//    MAP_GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
//    GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
//	
//	    //模拟开关控制引脚	
//    GPIO_setAsOutputPin(GPIO_PORT_P8, GPIO_PIN5| GPIO_PIN6);
//    GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN5| GPIO_PIN6);  //初始化拉高
//	    GPIO_setAsOutputPin(GPIO_PORT_P8, GPIO_PIN7| GPIO_PIN3);
//    GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN7| GPIO_PIN3);  //初始化拉高
}
void channelx(void)	//多倍频
{
	GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN2); 

}
void channely(void)	//单倍频
{
	GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN2); 

}

void Fre_channel0(void)
{
	GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN5); 
	GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN6);  
}

void Fre_channel2(void)
{
	GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN5); 
	GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN6);  
}
void Fre_channel1(void)
{
	GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN5); 
	GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN6);  
}
void Fre_channel3(void)
{
	GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN5); 
	GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN6);  
}

void two_Fre(void)
{
	GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN3); 
	GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN7);  
}

void three_Fre(void)
{
	GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN3); 
	GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN7);  
}
void four_Fre(void)
{
	GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN3); 
	GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN7); 
}
void five_Fre(void)
{
	GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN3); 
	GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN7);   
}

