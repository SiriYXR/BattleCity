#include"functions.h"


int myrand_int(int min,int max)
{
	// randomf() 返回一个 0 到 1 之间的随机浮点数
	int i;
	
	while (true)
	{
		i = (int)(randomf() * max);
		if (i >= min && i <= max)
			break;
	}
	return i;
}