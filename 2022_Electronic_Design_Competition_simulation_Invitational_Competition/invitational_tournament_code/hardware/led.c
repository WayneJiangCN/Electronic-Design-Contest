/*
 * led.c
 *
 *  Created on: 2020��9��10��
 *      Author: 60495
 */
#include "led.h"

void LED_Init(void)
{
//    GPIO_setAsOutputPin(GPIO_PORT_P10, GPIO_PIN3);
//    GPIO_setAsOutputPin(GPIO_PORT_P10, GPIO_PIN0);
//
//    GPIO_setOutputLowOnPin(GPIO_PORT_P10, GPIO_PIN3);
//    GPIO_setOutputLowOnPin(GPIO_PORT_P10, GPIO_PIN0);  //��ʼ������
	 GPIO_setAsOutputPin(GPIO_PORT_P8, GPIO_PIN2);	//����
	 GPIO_setAsOutputPin(GPIO_PORT_P8, GPIO_PIN5| GPIO_PIN6); //�˲�
	 GPIO_setAsOutputPin(GPIO_PORT_P8, GPIO_PIN3| GPIO_PIN7); //��Ƶ

	 GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN2);  //��ʼ������
    GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN5| GPIO_PIN6);  //��ʼ������
	 GPIO_setOutputHighOnPin(GPIO_PORT_P8,  GPIO_PIN3| GPIO_PIN7);  //��ʼ������

//    MAP_GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
//    GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
//	
//	    //ģ�⿪�ؿ�������	
//    GPIO_setAsOutputPin(GPIO_PORT_P8, GPIO_PIN5| GPIO_PIN6);
//    GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN5| GPIO_PIN6);  //��ʼ������
//	    GPIO_setAsOutputPin(GPIO_PORT_P8, GPIO_PIN7| GPIO_PIN3);
//    GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN7| GPIO_PIN3);  //��ʼ������
}
void channelx(void)	//�౶Ƶ
{
	GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN2); 

}
void channely(void)	//����Ƶ
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

