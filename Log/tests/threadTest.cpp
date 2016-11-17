#include<thread>
#include<iostream>
using namespace std;
void fun()
{
cout<<"fun"<<endl;
}
int main()
{
thread t;
t=std::move(thread(fun));
t.join();
return 1;
}
