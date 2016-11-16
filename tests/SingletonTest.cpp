#include<iostream>
#include<thread>
#include<vector>
#include"../Singleton.h"
using namespace std;
class test{
public:
	test(){
		cout<<"exec test"<<endl;
		}
	
	};
void fun(){
	Singleton<test>::instance();
}
int main(){
	vector<thread> v;
	for(int i=0;i<5;++i)
		v.push_back(thread(fun));

	for(int i=0;i<5;++i)
		v[i].join();
	
	return 0;
	}
