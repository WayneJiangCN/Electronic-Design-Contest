/*
 * my_usart.c
 *
 *  Created on: 2020年10月11日
 *      Author: 60495
 */
#include "my_usart.h"
#include "stdarg.h"
#include "stdio.h"
#include "string.h"

uint8_t EUSCI_A2_TX_BUF[EUSCI_A2_SEND_LEN];   //发送缓冲,最大USART2_MAX_SEND_LEN字节
uint8_t EUSCI_A2_RX_BUF[EUSCI_A2_REC_LEN];   //接收缓冲,最大EUSCI_A2_REC_LEN个字节.
//接收状态
//bit15，    接收完成标志;1完成
//bit14，    接收到0x0d;1接收到0x0d
//bit13~0，  接收到的有效字节数目
uint16_t EUSCI_A2_RX_STA=0;       //接收状态标记

/* UART Configuration Parameter. These are the configuration parameters to
 * make the eUSCI A UART module to operate with a 115200 baud rate. These
 * values were calculated using the online calculator that TI provides
 * at:
 * http://software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/MSP430BaudRateConverter/index.html
 */
const eUSCI_UART_ConfigV1 uartConfig2 =
{
        EUSCI_A_UART_CLOCKSOURCE_SMCLK,          // SMCLK Clock Source
        26,                                      // BRDIV = 26
        0,                                       // UCxBRF = 0
        37,                                      // UCxBRS = 37
        EUSCI_A_UART_NO_PARITY,                  // No Parity
        EUSCI_A_UART_LSB_FIRST,                  // LSB First
        EUSCI_A_UART_ONE_STOP_BIT,               // One stop bit
        EUSCI_A_UART_MODE,                       // UART mode
        EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION,  // Oversampling
        EUSCI_A_UART_8_BIT_LEN                  // 8 bit data length
};

void usart2_init(void)
{
    /* Selecting P1.2 and P1.3 in UART mode and P1.0 as output (LED) */
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P3,
            GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);

    /* Setting DCO to 24MHz (upping Vcore) */     //不用DCO时钟源了，SMCLK时钟源选择HFXT外部 48Mhz
//    FlashCtl_setWaitState(FLASH_BANK0, 1);
//    FlashCtl_setWaitState(FLASH_BANK1, 1);  //改变内部时钟必须的操作
//    MAP_PCM_setCoreVoltageLevel(PCM_VCORE1);
//    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_24);

    /* Configuring UART Module */
    MAP_UART_initModule(EUSCI_A2_BASE, &uartConfig2);

    /* Enable UART module */
    MAP_UART_enableModule(EUSCI_A2_BASE);

    /* Enabling interrupts */
    MAP_UART_enableInterrupt(EUSCI_A2_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
    MAP_Interrupt_enableInterrupt(INT_EUSCIA2);
}

///**
//*改写printf
//*改标MINI板标准库的函数
//*/
void UA2_printf(char* fmt,...)
{
    unsigned int k=0;
    va_list ap;
    va_start(ap,fmt);
    vsprintf((char*)EUSCI_A2_TX_BUF,fmt,ap);
    va_end(ap);
  do
  {
    MAP_UART_transmitData(EUSCI_A2_BASE, *(EUSCI_A2_TX_BUF + k));
    k++;
  } while(*(EUSCI_A2_TX_BUF + k)!='\0');
}

/* EUSCI A3 UART ISR - Echos data back to PC host */
void EUSCIA2_IRQHandler(void)
{
    uint8_t Res;
    uint32_t status = MAP_UART_getEnabledInterruptStatus(EUSCI_A2_BASE);
    if(status & EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG)
    {
        Res=UART_receiveData(EUSCI_A2_BASE);
        if((EUSCI_A2_RX_STA&0x8000)==0)//接收未完成
        {
            if(EUSCI_A2_RX_STA&0x4000) /* 接收到了0xff */
            {
                if(Res!=0x0a)EUSCI_A2_RX_STA=0; /* 接收错误,重新开始 */
                else EUSCI_A2_RX_STA|=0x8000; //接收完成了
							
            }
            else /* 还没收到0Xff */
            {
                if(Res==0x0d)EUSCI_A2_RX_STA|=0x4000;
                else
                {
                    EUSCI_A2_RX_BUF[EUSCI_A2_RX_STA&0X3FFF]=Res ;
                    EUSCI_A2_RX_STA++;
                    if(EUSCI_A2_RX_STA>(EUSCI_A2_REC_LEN-1))EUSCI_A2_RX_STA=0;//接收数据错误,重新开始接收
                }
            }
        }
    }
//    uint8_t len,i; //接收数据长度
//    //如果接收指令完成
//    if(EUSCI_A2_RX_STA&0x8000)  //判断是否接触屏
//    {
//     len=EUSCI_A2_RX_STA&0x3fff;//得到此次接收到的数据长度
//     for(i=0;i<len;i++)
//    {
//        recevchar(EUSCI_A2_RX_BUF[i]);
//
//    }
//     EUSCI_A2_RX_STA=0;    //清空标志
//    //2019/2/20新增,解决来回跳转BUG
//    }
    MAP_Interrupt_disableSleepOnIsrExit();  //必须清楚标志位否则卡死
}

void TJC_Send(char * buf1)
{
    uint8_t i=0;
    uint8_t buf;
    uint8_t cat=0xff;

  while (1)
 {
     if (buf1[i]!=0)
    {
       buf=buf1[i];
       MAP_UART_transmitData(EUSCI_A2_BASE, buf);
     while((EUSCI_A2->STATW)&0x01);       //等待发送结束
     i++;
    }
    else break; //退出循环
  }
 /******************发送结束符****************/
     MAP_UART_transmitData(EUSCI_A2_BASE, cat);
     while((EUSCI_A2->STATW)&0x01);       //等待发送结束
     MAP_UART_transmitData(EUSCI_A2_BASE, cat);
     while((EUSCI_A2->STATW)&0x01);       //等待发送结束
     MAP_UART_transmitData(EUSCI_A2_BASE, cat);
     while((EUSCI_A2->STATW)&0x01);       //等待发送结束
}
