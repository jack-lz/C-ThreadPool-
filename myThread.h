#pragma once
#ifndef MYTHREAD
#define MYTHREAD
#include <iostream>
#include <windows.h>
//线程要做的事情
typedef unsigned int(*jobFunction)(int num,WPARAM wParam, LPARAM lParam);
//线程完成后回调
typedef void(*jobCallback)(unsigned int pResult);
class MyThread
{
public:
	MyThread();
	~MyThread();
	bool isWorking();//是否在工作
	void doJob(jobFunction jobPrac, int num,WPARAM wParam, LPARAM lParam, jobCallback cb);   //指派任务
private:
	bool bIsWorking;
	jobFunction m_jobFunc;
	jobCallback m_jobCallback;
	int num;
	WPARAM wParam;
	LPARAM lParam;
	HANDLE m_pHread;
	void jobDone();// 线程挂起
	static DWORD WINAPI threadProc(LPARAM lParam);   //真正线程
};
#endif // MYTHREAD