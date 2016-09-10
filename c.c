@@name 测试程序运行时间

#include <stdio.h>
#include <time.h>

clock_t start,stop;

double duration;

int main()
{
	start = clock();
	MyFunction();
	stop = clock();
	duration = ((double)(stop-start))/CLK_TCK;

	return 0;
}
