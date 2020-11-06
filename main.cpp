#include <mutex>
#include "Mypool.h"
 
//typedef unsigned int(*jobFunction)(WPARAM wParam, LPARAM lParam);
//typedef void(*jobCallback)(unsigned int pResult);
mutex m;
unsigned int job(WPARAM wParam, LPARAM lParam)
{
	m.lock();
	printf("job doing :%d + %d = ?\n", wParam, lParam);
	//Sleep(500);
	return lParam + wParam;
	m.unlock();
}
unsigned int job1(int num,WPARAM wParam, LPARAM lParam)
{
	printf("job doing :1+2+3+...+%d= ?\n", num);
	return num *(num -1)/2;
}
void cb(unsigned int pResult)
{
	printf("job result:%d\n",pResult);
}
int main()
{
	MyPool *pool = new MyPool(2);
	while (true)
	{
		char cmd = getchar();
		if (cmd == 'q' || cmd == 'Q')
		{
			break;
		}
		printf("thread pool size :%d\n",pool->getPoolSize());
		pool->pushJob(job1,100,0,0,cb);
	}
	printf("process exit\n");
	return 0;
}

