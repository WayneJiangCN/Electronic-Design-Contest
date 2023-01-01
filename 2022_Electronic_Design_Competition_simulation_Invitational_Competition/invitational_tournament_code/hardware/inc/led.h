/*
 * led.h
 *
 *  Created on: 2020年9月10日
 *      Author: 60495
 */

#ifndef APP_LED_LED_H_
#define APP_LED_LED_H_
#include "sysinit.h"


void Fre_channel0(void);
void Fre_channel1(void);
void Fre_channel2(void);
void Fre_channel3(void);
void channelx(void);	//多倍频
void channely(void);	
void LED_Init(void);

void two_Fre(void);
void three_Fre(void);
void four_Fre(void);
void five_Fre(void);

#endif /* APP_LED_LED_H_ */
