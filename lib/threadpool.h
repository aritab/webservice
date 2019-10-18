#ifndef THREADPOOL_H
#define THREADPOOL_H
#include<list>
#include<cstdio>
#include<exception>
#include<pthread.h>
#include "locker.h"
template<typename T>
class threadpool{
	public:
	threadpool(int thread_number=8, int max_requests=10000);
	~threadpool();
	bool append(T* request);
	private:
	static void* worker(void* arg);
	void run;
	private:
	int m_thread_number;
	int m_max_requests;
	pthread_t* m_threads;
	std::list<T* > m_workqueue;
	sem m_queuestat;
	bool m_stop;
};

template<typename T>
threadpool<T>::threadpool(int thread_number, int max_requests):m_thread_number(thread_number),m_max_requests(max_requests),m_stop(false),m_threads(NULL){
	if((thread_number<=0)||(max_requests<=0)){
		throw std::exception();
	}
	m_threads=new pthread_t(m_thread_number);
	if(!m_threads){
		throw std::exception();
	}
	for(int i=0;i<thread_number;++i){
		printf("create the %dth thread\n",i);
		if(pthread_create(m_threads+i,NULL,worker,this)!=0){
			
		}
	}
}





























