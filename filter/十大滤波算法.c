//滑动滤波
//设置一个缓存区，剔除最旧数据，将新数据添加到缓存区，再取缓存区里面现有数据的平均值，以此循环。
#define NUM 10		// 缓存区大小
float filter(int16_t data)
{
	static int16_t buf[NUM];
	static int16_t index=0,flag=0;
	static float sum=0;
	
	// 替换之前位置上的数据
	sum += data - buf[index];	
	buf[index] = data;
	index++;
	
	// 控制数据循环放置到缓冲区
	if(index==NUM)
	{
		index = 0;
		flag = 1;
	}
	
	// 如果没有充满缓存区，有几个就取几个的平均
	if(flag==0)		return sum/index;
	else			return sum/NUM;
}
————————————————
版权声明：本文为CSDN博主「xflySnail」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/u012902367/article/details/88710022 