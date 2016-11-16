#ifndef __CONDITION__
#define __CONDITION__
#include<pthread.h>
#include"Mutex.h"
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


private:
	MutexLock &mutex;
	pthread_cond_t pcond;
	};
#endif
