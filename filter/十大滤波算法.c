//�����˲�
//����һ�����������޳�������ݣ�����������ӵ�����������ȡ�����������������ݵ�ƽ��ֵ���Դ�ѭ����
#define NUM 10		// ��������С
float filter(int16_t data)
{
	static int16_t buf[NUM];
	static int16_t index=0,flag=0;
	static float sum=0;
	
	// �滻֮ǰλ���ϵ�����
	sum += data - buf[index];	
	buf[index] = data;
	index++;
	
	// ��������ѭ�����õ�������
	if(index==NUM)
	{
		index = 0;
		flag = 1;
	}
	
	// ���û�г������������м�����ȡ������ƽ��
	if(flag==0)		return sum/index;
	else			return sum/NUM;
}
��������������������������������
��Ȩ����������ΪCSDN������xflySnail����ԭ�����£���ѭCC 4.0 BY-SA��ȨЭ�飬ת���븽��ԭ�ĳ������Ӽ���������
ԭ�����ӣ�https://blog.csdn.net/u012902367/article/details/88710022 