#pragma once
#include <vector>
#include "Mythread.h"
using namespace std;
#ifndef MYPOOL
#define MYPOOL
 
/*
池的概念:预先从操作系统申请大片资源,然后使用后不还给系统,保持复用
优点:避免频繁从应用层切换到内核<操作系统申请资源需要嵌入内核当中去>
*/
 
/*
线程池管理类,需要作为一个管理者,管理N个线程
*/
class MyPool
{
public:
	MyPool(int nSize);
	~MyPool();
	bool pushJob(jobFunction jobPrac, int num,WPARAM wParam, LPARAM lParam, jobCallback cb);
	int getPoolSize();
private:
	vector<MyThread *>m_threadVector;
};
 
#endif // !MYPOOL

