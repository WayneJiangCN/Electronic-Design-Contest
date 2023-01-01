/****************************************************/
//MSP432P401R
//ADC采集
//Bilibili：m-RNA
//E-mail:m-RNA@qq.com
//创建日期:2021/9/13
/****************************************************/

/*********************
 *
 * 最大采集电压 3.3V
 *
 * ADC采集引脚：
 * 单路 为 P5.5
 * 双路 为 P5.5 P5.4
 * 三路 为 P5.5 P5.4 P5.3
 *
 ************************/
 
#include "adc.h"
#include "usart.h"
extern uint16_t AD_wave_ram[500];
extern uint16_t AD_store_point;
extern uint16_t  AD_sample_ok;
 extern uint16_t adcv1[500];
  extern uint16_t adcv2[500];
static uint16_t resultsBuffer[2];
Timer_A_UpModeConfig upModeConfig =
{
        TIMER_A_CLOCKSOURCE_SMCLK,            // SMCLK Clock Source
        TIMER_A_CLOCKSOURCE_DIVIDER_1,        // SMCLK/1 = 48MHz
        240,                                  // 设置为240装载值 1M
        TIMER_A_TAIE_INTERRUPT_DISABLE,       // Disable Timer ISR
        TIMER_A_CCIE_CCR0_INTERRUPT_DISABLE,  // Disable CCR0
        TIMER_A_DO_CLEAR                      // Clear Counter
};

/* Timer_A Compare Configuration Parameter */
Timer_A_CompareModeConfig compareConfig =
{
        TIMER_A_CAPTURECOMPARE_REGISTER_1,          // Use CCR1
        TIMER_A_CAPTURECOMPARE_INTERRUPT_DISABLE,   // 禁止 CCR interrupt
        TIMER_A_OUTPUTMODE_SET_RESET,               // 取反输出
        240                                      // Period 47 48000000/48=1M 
};

void Change_SAMPLE_Rate(int sample)
{
    upModeConfig.timerPeriod = sample;
    compareConfig.compareValue = sample;

    /* Configuring Timer_A in continuous mode and sourced from ACLK */
    MAP_Timer_A_configureUpMode(TIMER_A0_BASE, &upModeConfig);

    /* Configuring Timer_A0 in CCR2 to trigger at 16000 (0.5s) */
    MAP_Timer_A_initCompare(TIMER_A0_BASE, &compareConfig);
}
/**
 * function:内部adc初始化，单通道模式
 * parameter:NONE
 * return:NONE
 * note:定时器触发采样，中断读取采样值
 */
void adc_init1(void)
{
    /* Initializing ADC (MCLK/1/1) */
    MAP_ADC14_enableModule();
    MAP_ADC14_initModule(ADC_CLOCKSOURCE_MCLK, ADC_PREDIVIDER_1, ADC_DIVIDER_1,
            0);

    /* Configuring GPIOs (6.0 A15) */
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P5, GPIO_PIN5|GPIO_PIN4,
    GPIO_TERTIARY_MODULE_FUNCTION);
 MAP_ADC14_configureMultiSequenceMode(ADC_MEM0, ADC_MEM1, true);
    /* Configuring ADC Memory */
  //  MAP_ADC14_configureSingleSampleMode(ADC_MEM15, true);  //采样结果存放位置
    MAP_ADC14_configureConversionMemory(ADC_MEM0, ADC_VREFPOS_AVCC_VREFNEG_VSS,     //REF=3.3V=FSR
    ADC_INPUT_A0, false);  //单端输入模式
	   MAP_ADC14_configureConversionMemory(ADC_MEM1, ADC_VREFPOS_AVCC_VREFNEG_VSS,     //REF=3.3V=FSR
    ADC_INPUT_A1, false);  //单端输入模式

    /* Configuring Timer_A in continuous mode and sourced from ACLK */
    MAP_Timer_A_configureUpMode(TIMER_A0_BASE, &upModeConfig);//增计数模式

    /* Configuring Timer_A0 in CCR1 to trigger at 16000 (0.5s) */
    MAP_Timer_A_initCompare(TIMER_A0_BASE, &compareConfig);//配置CCR1

    /* Configuring the sample trigger to be sourced from Timer_A0  and setting it
     * to automatic iteration after it is triggered*/
    MAP_ADC14_setSampleHoldTrigger(ADC_TRIGGER_SOURCE1, false);    //TA0_C1触发源，触发源选择查看P401R芯片手册127页，ADC_TRIGGER_SOURCE1=TA0_C1,ADC_TRIGGER_SOURCE2=TA0_C2,ADC_TRIGGER_SOURCE3=TA1_C1,ADC_TRIGGER_SOURCE4=TA1_C2,ADC_TRIGGER_SOURCE5=TA2_C1

    /* Enabling the interrupt when a conversion on channel 1 is complete and
     * enabling conversions */
    MAP_ADC14_enableInterrupt(ADC_INT1);
    MAP_ADC14_enableConversion();

    /* Enabling Interrupts */
    MAP_Interrupt_enableInterrupt(INT_ADC14);
    MAP_Interrupt_enableMaster();

   /* Starting the Timer */
    MAP_Timer_A_startCounter(TIMER_A0_BASE, TIMER_A_UP_MODE);
    /* Stop the Timer */
  //  MAP_Timer_A_stopTimer(TIMER_A0_BASE);

}
/* This interrupt is fired whenever a conversion is completed and placed in
 * ADC_MEM0 */
void ADC14_IRQHandler(void)
{
    uint64_t status;
	

    status = MAP_ADC14_getEnabledInterruptStatus();
    MAP_ADC14_clearInterruptFlag(status);

    if (status & ADC_INT1)
    {
		 MAP_ADC14_getMultiSequenceResult(resultsBuffer);
        adcv1[AD_store_point]=resultsBuffer[0];
		 adcv2[AD_store_point]=resultsBuffer[1];
		 AD_store_point++;
        if(AD_store_point==200)
        {
            AD_store_point=0;
            AD_sample_ok=1;  //采样完成
        }
    }
}
