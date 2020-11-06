#include "Mypool.h"
 
//在构造在初始化几个线程
MyPool::MyPool(int nSize)
{
	m_threadVector.clear();
	for (int i = 0; i < nSize; ++i)
	{
		MyThread *tmp = new MyThread();
		m_threadVector.push_back(tmp);
	}
}
MyPool::~MyPool()
{
	vector<MyThread *>::iterator iter = m_threadVector.begin();
	for (; iter != m_threadVector.end(); iter++)
	{
		MyThread *tmp = *iter;
		delete tmp;
	}
}
 
bool MyPool::pushJob(jobFunction jobPrac, int num,WPARAM wParam, LPARAM lParam, jobCallback cb)
{
	vector<MyThread *>::iterator iter = m_threadVector.begin();
	for (;iter != m_threadVector.end();iter++)
	{
		MyThread *tmp = *iter;
		if (!tmp->isWorking())
		{
			tmp->doJob(jobPrac, num,wParam, lParam, cb);
			return true;
		}
	}
	MyThread *tmp = new MyThread();
	m_threadVector.push_back(tmp);
	tmp->doJob(jobPrac,num, wParam, lParam, cb);
	return true;
}
 
int MyPool::getPoolSize()
{
	return m_threadVector.size();
}

