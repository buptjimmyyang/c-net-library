#include<iostream>
#include"../Mutex.h"
#include"../Condition.h"
#include<vector>
#include<thread>
using namespace std;

class CountDownLatch
{
private:
	mutable MutexLock mutex;
	Condition cond;
	int count;
public:
	explicit CountDownLatch(int count_):cond(mutex),count(count_){
		
		
		
		}
	void wait(){
		MutexLockGuard lock(mutex);
		while(count>0)
			cond.wait();
		}
	int getCount(){
		MutexLockGuard lock(mutex);
		return count;
		}
	void countDown(){
		MutexLockGuard lock(mutex);
		--count;
		if(count==0)
			cond.notifyAll();
		
		}
};

CountDownLatch count(10);
void fun1(){
	for(int i=0;i<11;++i){
	
	cout<<"reduce num fun"<<count.getCount()<<endl;
	count.countDown();
	}
	}
void fun2(int i){
	count.wait();
	cout<<"thread"+i<<'\t'<<count.getCount()<<endl;
	}
int main()
{
	vector<thread> v;
	for(int i=0;i<4;++i)
		v.push_back(thread(fun2,i+1));
	
	thread t(fun1);

	t.join();
	for(int i=0;i<4;++i)
		v[i].join();
	
	return 0;
	}

