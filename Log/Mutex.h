#ifndef __MUTEX__  
#define __MUTEX__  
/* 
define two class MutexLock and MutexLockGuard 
*/  
#include<pthread.h>  
class MutexLock  
{  
private:  
    pthread_mutex_t mutex_;  
public:  
    MutexLock(){  
    pthread_mutex_init(&mutex_,NULL);  
}  
    ~MutexLock(){  
    pthread_mutex_destroy(&mutex_);  
}  
    void lock(){  
    pthread_mutex_lock(&mutex_);  
}  
    void unlock(){  
    pthread_mutex_unlock(&mutex_);  
}  
    pthread_mutex_t*    getPthreadMutex(){  
    return &mutex_;  
}  
};  
class MutexLockGuard{  
private:  
    MutexLock &mutex;  
public:  
    explicit MutexLockGuard(MutexLock& mutex_):mutex(mutex_){  
    mutex.lock();  
}  
    ~MutexLockGuard(){  
    mutex.unlock();  
}  
  
};  
#endif  
