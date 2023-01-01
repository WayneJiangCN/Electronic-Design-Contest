//一阶低通滤波，alpha范围0~1
y = alpha*x + (1-alpha)*last_y;
last_y = y;
/*当alpha值调小时滞后现象会更明显，反之调大则会减缓滞后现象但同时噪声抑制能力下降*/