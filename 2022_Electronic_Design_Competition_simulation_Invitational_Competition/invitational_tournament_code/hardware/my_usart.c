/*
 * my_usart.c
 *
 *  Created on: 2020��10��11��
 *      Author: 60495
 */
#include "my_usart.h"
#include "stdarg.h"
#include "stdio.h"
#include "string.h"

uint8_t EUSCI_A2_TX_BUF[EUSCI_A2_SEND_LEN];   //���ͻ���,���USART2_MAX_SEND_LEN�ֽ�
uint8_t EUSCI_A2_RX_BUF[EUSCI_A2_REC_LEN];   //���ջ���,���EUSCI_A2_REC_LEN���ֽ�.
//����״̬
//bit15��    ������ɱ�־;1���
//bit14��    ���յ�0x0d;1���յ�0x0d
//bit13~0��  ���յ�����Ч�ֽ���Ŀ
uint16_t EUSCI_A2_RX_STA=0;       //����״̬���

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

    /* Setting DCO to 24MHz (upping Vcore) */     //����DCOʱ��Դ�ˣ�SMCLKʱ��Դѡ��HFXT�ⲿ 48Mhz
//    FlashCtl_setWaitState(FLASH_BANK0, 1);
//    FlashCtl_setWaitState(FLASH_BANK1, 1);  //�ı��ڲ�ʱ�ӱ���Ĳ���
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
//*��дprintf
//*�ı�MINI���׼��ĺ���
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
        if((EUSCI_A2_RX_STA&0x8000)==0)//����δ���
        {
            if(EUSCI_A2_RX_STA&0x4000) /* ���յ���0xff */
            {
                if(Res!=0x0a)EUSCI_A2_RX_STA=0; /* ���մ���,���¿�ʼ */
                else EUSCI_A2_RX_STA|=0x8000; //���������
							
            }
            else /* ��û�յ�0Xff */
            {
                if(Res==0x0d)EUSCI_A2_RX_STA|=0x4000;
                else
                {
                    EUSCI_A2_RX_BUF[EUSCI_A2_RX_STA&0X3FFF]=Res ;
                    EUSCI_A2_RX_STA++;
                    if(EUSCI_A2_RX_STA>(EUSCI_A2_REC_LEN-1))EUSCI_A2_RX_STA=0;//�������ݴ���,���¿�ʼ����
                }
            }
        }
    }
//    uint8_t len,i; //�������ݳ���
//    //�������ָ�����
//    if(EUSCI_A2_RX_STA&0x8000)  //�ж��Ƿ�Ӵ���
//    {
//     len=EUSCI_A2_RX_STA&0x3fff;//�õ��˴ν��յ������ݳ���
//     for(i=0;i<len;i++)
//    {
//        recevchar(EUSCI_A2_RX_BUF[i]);
//
//    }
//     EUSCI_A2_RX_STA=0;    //��ձ�־
//    //2019/2/20����,���������תBUG
//    }
    MAP_Interrupt_disableSleepOnIsrExit();  //���������־λ������
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
     while((EUSCI_A2->STATW)&0x01);       //�ȴ����ͽ���
     i++;
    }
    else break; //�˳�ѭ��
  }
 /******************���ͽ�����****************/
     MAP_UART_transmitData(EUSCI_A2_BASE, cat);
     while((EUSCI_A2->STATW)&0x01);       //�ȴ����ͽ���
     MAP_UART_transmitData(EUSCI_A2_BASE, cat);
     while((EUSCI_A2->STATW)&0x01);       //�ȴ����ͽ���
     MAP_UART_transmitData(EUSCI_A2_BASE, cat);
     while((EUSCI_A2->STATW)&0x01);       //�ȴ����ͽ���
}
