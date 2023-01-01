.//https://blog.csdn.net/moge19/article/details/81750731
/*
QֵΪ����������ԽСϵͳԽ�������������Ƕ�ģ��Ԥ���ֵ���ζ�Խ�ߣ�����̫С�����׷�ɢ�����QΪ�㣬��ô����ֻ����Ԥ��ֵ��QֵԽ�����Ƕ���Ԥ������ζȾ�Խ�ͣ����Բ���ֵ�����ζȾͱ�ߣ����Qֵ�������ô����ֻ���β���ֵ��

RֵΪ����������̫С̫�󶼲�һ�����ʡ�R̫�󣬿������˲���Ӧ���������Ϊ�����²�����ֵ�����ζȽ��ͣ�ԽСϵͳ����Խ�죬����С�����׳����𵴣�Rֵ�ĸı���Ҫ��Ӱ�쿨�����������ٶȡ�

����ʱ�����Ƚ�Q��С�����������R�Ӵ���С�������ȹ̶�һ��ֵȥ��������һ��ֵ���������ٶ��벨�������
��������������������������������
��Ȩ����������ΪCSDN��������ľ����ѧϰ�����ԭ�����£���ѭCC 4.0 BY-SA��ȨЭ�飬ת���븽��ԭ�ĳ������Ӽ���������
ԭ�����ӣ�https://blog.csdn.net/weixin_45751396/article/details/119595886
*/
unsigned long kalman_filter(unsigned long ADC_Value)
{
    float x_k1_k1,x_k_k1;
    static float ADC_OLD_Value;
    float Z_k;
    static float P_k1_k1;

    static float Q = 0.0003;    //�������
    static float R = 5;            //�������
    static float Kg = 0;
    static float P_k_k1 = 1;

    float kalman_adc;
    static float kalman_adc_old=0;
    Z_k = ADC_Value;
    x_k1_k1 = kalman_adc_old;

    x_k_k1 = x_k1_k1;
    P_k_k1 = P_k1_k1 + Q;

    Kg = P_k_k1/(P_k_k1 + R);

    kalman_adc = x_k_k1 + Kg * (Z_k - kalman_adc_old);
    P_k1_k1 = (1 - Kg)*P_k_k1;
    P_k_k1 = P_k1_k1;

    ADC_OLD_Value = ADC_Value;
    kalman_adc_old = kalman_adc;

    return get_int_num(kalman_adc);
}


//�޸ĺ�Ĵ���
unsigned long kalman_filter(unsigned long ADC_Value)
{
float x_k1_k1,x_k_k1;
static float ADC_OLD_Value;
float Z_k;
static float P_k1_k1;

static float Q = 0.0001;
static float R = 5;
static float Kg = 0;
static float P_k_k1 = 1;

float kalman_adc;
static float kalman_adc_old=0;

Z_k = ADC_Value;

if (abs(kalman_adc_old-ADC_Value)>=10)
{ 
    x_k1_k1= ADC_Value*0.382 + kalman_adc_old*0.618;
}else
{
    x_k1_k1 = kalman_adc_old;
}
x_k_k1 = x_k1_k1;
P_k_k1 = P_k1_k1 + Q;

Kg = P_k_k1/(P_k_k1 + R);

kalman_adc = x_k_k1 + Kg * (Z_k - kalman_adc_old);
P_k1_k1 = (1 - Kg)*P_k_k1;
P_k_k1 = P_k1_k1;

ADC_OLD_Value = ADC_Value;
kalman_adc_old = kalman_adc;

return get_int_num(kalman_adc);
}