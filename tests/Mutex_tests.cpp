#include<thread>
#include"../Mutex.h"
#include<iostream>
#include<vector>
using namespace std;
int i=0;
MutexLock mutex;
void threadFunc(){
	MutexLockGuard t(mutex);
	for(int j=0;j<10;++j){
	++i;
	cout<<i<<endl;
}

}
int main(){
vector<thread> v;
for(int j=0;j<10;++j){
	v.push_back(thread(threadFunc));
}
//thread t1(threadFunc);
//thread t2(threadFunc);
for(int j=0;j<10;++j){
	v[j].join();
}
//t1.join();
//t2.join();
return 0;
}
