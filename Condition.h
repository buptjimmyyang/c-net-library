#ifndef __CONDITION__
#define __CONDITION__
#include<pthread.h>
#include"Mutex.h"
#include<errno.h>
#include<stdint.h>
//添加评论3 jimmyyang
//this is a cpp condition
//添加评论5 master
class Condition
{
public:
	explicit Condition(MutexLock &mutex_):mutex(mutex_){
		pthread_cond_init(&pcond,NULL);
		}
	~Condition(){
		pthread_cond_destroy(&pcond);
		}
	void wait(){
		pthread_cond_wait(&pcond,mutex.getPthreadMutex());

		}
	void notify(){
		pthread_cond_signal(&pcond);
		}
	
	void notifyAll(){
		pthread_cond_broadcast(&pcond);
		}

	bool waitForSeconds(double seconds)
	{
		struct timespec abstime;
		clock_gettime(CLOCK_REALTIME,&abstime);
		const int64_t ks=1e9;

		int64_t nanoseconds=static_cast<int64_t>(seconds*ks);

		abstime.tv_sec+=static_cast<time_t>((abstime.tv_nsec+nanoseconds)/ks);
		abstime.tv_nsec+=static_cast<long>((abstime.tv_nsec+nanoseconds)%ks);
		return ETIMEDOUT==pthread_cond_timedwait(&pcond,mutex.getPthreadMutex(),&abstime);
	}
private:
	MutexLock &mutex;
	pthread_cond_t pcond;
	};
#endif
