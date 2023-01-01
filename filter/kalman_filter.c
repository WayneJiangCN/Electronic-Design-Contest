.//https://blog.csdn.net/moge19/article/details/81750731
/*
Q值为过程噪声，越小系统越容易收敛，我们对模型预测的值信任度越高；但是太小则容易发散，如果Q为零，那么我们只相信预测值；Q值越大我们对于预测的信任度就越低，而对测量值的信任度就变高；如果Q值无穷大，那么我们只信任测量值；

R值为测量噪声，太小太大都不一定合适。R太大，卡尔曼滤波响应会变慢，因为它对新测量的值的信任度降低；越小系统收敛越快，但过小则容易出现震荡；R值的改变主要是影响卡尔曼的收敛速度。

测试时可以先将Q从小往大调整，将R从大往小调整；先固定一个值去调整另外一个值，看收敛速度与波形输出。
————————————————
版权声明：本文为CSDN博主「三木今天学习了嘛」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/weixin_45751396/article/details/119595886
*/
unsigned long kalman_filter(unsigned long ADC_Value)
{
    float x_k1_k1,x_k_k1;
    static float ADC_OLD_Value;
    float Z_k;
    static float P_k1_k1;

    static float Q = 0.0003;    //过程误差
    static float R = 5;            //测量误差
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


//修改后的代码
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