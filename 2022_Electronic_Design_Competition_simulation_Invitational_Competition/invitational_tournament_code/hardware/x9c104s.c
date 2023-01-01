#include "x9c104s.h"
#include "delay.h"

void x9c104s_init(void)
{
	GPIO_setAsOutputPin(GPIO_PORT_P8, GPIO_PIN5| GPIO_PIN6|GPIO_PIN7);
    GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN5| GPIO_PIN6|GPIO_PIN7);  //初始化拉高
}


void add_R(uint8_t n)
{

	C_S(0);
	delay_us(1);
	U_D(1);
	delay_us(1);
	
	for(int i=0;i<n;i++)
	{
	INC(1);
	delay_us(1);
	INC(0);
	delay_us(1);
	}
	delay_us(2); 
	C_S(1);
	U_D(1);
}
// R=1010*n+40;
void decrease_R(uint8_t n)
{

	C_S(0);
	delay_us(1);
	U_D(0);
	delay_us(1);
	for(int i=0;i<n;i++)
	{
	INC(1);
	delay_us(1);
	INC(0);
	delay_us(1);
	}
	delay_us(2);
	C_S(1);
	U_D(1);

}