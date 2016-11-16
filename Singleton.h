
#ifndef __SINGLETON__
#define __SINGLETON__
#include<pthread.h>
template<typename T>
class Singleton{
private:
	static pthread_once_t ponce;
	static T* value;
public:
	static T& instance(){
		pthread_once(&ponce,&Singleton::init);
		}
	static void init(){
//		cout<<"exec init"<<endl;
		value=new T();
		}
	
};
template<typename T>
pthread_once_t Singleton<T>::ponce=PTHREAD_ONCE_INIT;

template<typename T>
T *Singleton<T>::value=NULL;

#endif

