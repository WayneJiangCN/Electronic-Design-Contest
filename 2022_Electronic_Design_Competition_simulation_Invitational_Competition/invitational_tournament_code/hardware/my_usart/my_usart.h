/*
 * my_usart.h
 *
 *  Created on: 2020年10月11日
 *      Author: 60495
 */

#ifndef APP_MY_USART_MY_USART_H_
#define APP_MY_USART_MY_USART_H_
#include "sysinit.h"

#define EUSCI_A3_SEND_LEN          50
#define EUSCI_A3_REC_LEN           200     //定义最大接收字节数 200

extern uint8_t EUSCI_A3_RX_BUF[EUSCI_A3_REC_LEN];
extern uint16_t EUSCI_A3_RX_STA;

void usart3_init(void);
void UA3_printf(char* fmt,...);
void TJC_Send(char * buf1);

#endif /* APP_MY_USART_MY_USART_H_ */
