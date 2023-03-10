#ifndef _AD9959_H_
#define _AD9959_H_
//#include "sys.h"
//#include "stdint.h"
#include "main.h"
#include "gpio.h"
//AD9959寄存器地址定义
#define CSR_ADD   0x00   //CSR 通道选择寄存器
#define FR1_ADD   0x01   //FR1 功能寄存器1
#define FR2_ADD   0x02   //FR2 功能寄存器2
#define CFR_ADD   0x03   //CFR 通道功能寄存器
#define CFTW0_ADD 0x04   //CTW0 通道频率转换字寄存器
#define CPOW0_ADD 0x05   //CPW0 通道相位转换字寄存器
#define ACR_ADD   0x06   //ACR 幅度控制寄存器
#define LSRR_ADD  0x07   //LSR 通道线性扫描寄存器
#define RDW_ADD   0x08   //RDW 通道线性向上扫描寄存器
#define FDW_ADD   0x09   //FDW 通道线性向下扫描寄存器
//AD9959管脚宏定义
#define CS_SET			HAL_GPIO_WritePin(CS_GPIO_Port,CS_Pin,GPIO_PIN_SET)
#define CS_RESET		HAL_GPIO_WritePin(CS_GPIO_Port,CS_Pin,GPIO_PIN_RESET)
#define SCLK_SET		HAL_GPIO_WritePin(SCLK_GPIO_Port,SCLK_Pin,GPIO_PIN_SET)
#define SCLK_RESET	HAL_GPIO_WritePin(SCLK_GPIO_Port,SCLK_Pin,GPIO_PIN_RESET)
#define UPDATE_SET	HAL_GPIO_WritePin(UPDATE_GPIO_Port,UPDATE_Pin,GPIO_PIN_SET)
#define UPDATE_RESET	HAL_GPIO_WritePin(UPDATE_GPIO_Port,UPDATE_Pin,GPIO_PIN_RESET)
#define PS0_SET			HAL_GPIO_WritePin(PS0_GPIO_Port,PS0_Pin,GPIO_PIN_SET)
#define PS0_RESET			HAL_GPIO_WritePin(PS0_GPIO_Port,PS0_Pin,GPIO_PIN_RESET)
#define PS1_SET			HAL_GPIO_WritePin(PS1_GPIO_Port,PS1_Pin,GPIO_PIN_SET)
#define PS1_RESET			HAL_GPIO_WritePin(PS1_GPIO_Port,PS1_Pin,GPIO_PIN_RESET)
#define PS2_SET			HAL_GPIO_WritePin(PS2_GPIO_Port,PS2_Pin,GPIO_PIN_SET)
#define PS2_RESET			HAL_GPIO_WritePin(PS2_GPIO_Port,PS2_Pin,GPIO_PIN_RESET)
#define PS3_SET			HAL_GPIO_WritePin(PS3_GPIO_Port,PS3_Pin,GPIO_PIN_SET)
#define PS3_RESET			HAL_GPIO_WritePin(PS3_GPIO_Port,PS3_Pin,GPIO_PIN_RESET)
#define SDIO0_SET		HAL_GPIO_WritePin(SDIO0_GPIO_Port,SDIO0_Pin,GPIO_PIN_SET)
#define SDIO0_RESET		HAL_GPIO_WritePin(SDIO0_GPIO_Port,SDIO0_Pin,GPIO_PIN_RESET)
#define SDIO1_SET		HAL_GPIO_WritePin(SDIO1_GPIO_Port,SDIO1_Pin,GPIO_PIN_SET)
#define SDIO1_RESET		HAL_GPIO_WritePin(SDIO1_GPIO_Port,SDIO1_Pin,GPIO_PIN_RESET)
#define SDIO2_SET		HAL_GPIO_WritePin(SDIO2_GPIO_Port,SDIO2_Pin,GPIO_PIN_SET)
#define SDIO2_RESET		HAL_GPIO_WritePin(SDIO2_GPIO_Port,SDIO2_Pin,GPIO_PIN_RESET)
#define SDIO3_SET		HAL_GPIO_WritePin(SDIO3_GPIO_Port,SDIO3_Pin,GPIO_PIN_SET)
#define SDIO3_RESET		HAL_GPIO_WritePin(SDIO3_GPIO_Port,SDIO3_Pin,GPIO_PIN_RESET)
#define AD9959_PWR_SET	HAL_GPIO_WritePin(AD9959_PWR_GPIO_Port,AD9959_PWR_Pin,GPIO_PIN_SET)
#define AD9959_PWR_RESET	HAL_GPIO_WritePin(AD9959_PWR_GPIO_Port,AD9959_PWR_Pin,GPIO_PIN_RESET)
#define Reset_SET		HAL_GPIO_WritePin(Reset_GPIO_Port,Reset_Pin,GPIO_PIN_SET)
#define Reset_RESET		HAL_GPIO_WritePin(Reset_GPIO_Port,Reset_Pin,GPIO_PIN_RESET)

void delay1 (uint32_t length);
void IntReset(void);	  //AD9959复位
void IO_Update(void);   //AD9959更新数据
void Intserve(void);		   //IO口初始化
void WriteData_AD9959(uint8_t RegisterAddress, uint8_t NumberofRegisters, uint8_t *RegisterData,uint8_t temp);
void Init_AD9959(void);
void Write_frequence(uint8_t Channel,uint32_t Freq);
void Write_Amplitude(uint8_t Channel, uint16_t Ampli);
void Write_Phase(uint8_t Channel,uint16_t Phase);

#endif


