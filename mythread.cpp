#include "Mythread.h"
MyThread::MyThread()
{
	 bIsWorking = false;
	 m_jobFunc = 0;
	 m_jobCallback = 0;
	 num = 0;
	 wParam = 0;
	 lParam = 0;
	//m_pHread = INVALID_HANDLE_VALUE;
	 //创建线程
	m_pHread = CreateThread(0,0,(LPTHREAD_START_ROUTINE)threadProc,this,0,0); 
	printf("new thread %08x\n",m_pHread);
}
MyThread::~MyThread()
{
	//if (m_pHread != INVALID_HANDLE_VALUE)
	//{
	//	TerminateThread(m_pHread,0); //强制自杀
	//}
		if (m_pHread != INVALID_HANDLE_VALUE)
		{
			m_jobCallback = (jobCallback)INVALID_HANDLE_VALUE;
			m_jobFunc = (jobFunction)INVALID_HANDLE_VALUE;
			ResumeThread(m_pHread);
			WaitForSingleObject(m_pHread,INFINITE);
			CloseHandle(m_pHread);
		}
}
bool MyThread::isWorking()
{
	return this->bIsWorking;
}
void MyThread::jobDone()
{
	this->bIsWorking = false;
	SuspendThread(m_pHread);  //休眠
	//printf("thread %08x job done\n",m_pHread);
}
/*
执行一个具体的任务
*/
void MyThread::doJob(jobFunction jobPrac,int num, WPARAM wParam, LPARAM lParam, jobCallback cb)
{
	this->num = num;
	this->m_jobCallback = cb;
	this->m_jobFunc = jobPrac;
	this->wParam = wParam;
	this->lParam = lParam;
	ResumeThread(m_pHread);  //ResumeThread(）使用该函数能够激活线程的运行，
							 //使CPU分配资源让线程恢复运行。
	printf("thread %08x start work..num %d wParam %d lParam  %d\n",m_pHread, num,wParam, lParam);
}
/*
真正的线程函数
*/
DWORD WINAPI MyThread::threadProc(LPARAM lParam)
{
	MyThread *pthis = (MyThread *)lParam;
	while (true)
	{  //因为线程在构造函数中申请的,但是申请的时候没有具体的任务
		if (pthis->m_jobCallback == INVALID_HANDLE_VALUE || pthis->m_jobFunc == INVALID_HANDLE_VALUE)
		{
			printf("thread %08x see byebye",pthis->m_pHread);
			break;
		}
		if (pthis->m_jobCallback == 0 || pthis->m_jobFunc == 0)
		{
			pthis->jobDone();
			//return;   不能直接return
			//continue;
		}
		pthis->bIsWorking = true;
		unsigned int result = pthis->m_jobFunc(pthis->num,pthis->wParam,pthis->lParam);
		printf("thread %08x job result %d\n",pthis->m_pHread,result);
		pthis->m_jobCallback(result);
		pthis->jobDone();
	}
	return 0;
}

