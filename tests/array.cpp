#include<iostream>
#include<string.h>
using namespace std;
void fun1(const char *arr){
	cout<<strlen(arr)<<endl;
	}
template<int N>
void fun2(const char(&arr)[N]){
	
	cout<<N<<endl;
	}
int main(){
const	char *a="abcdef";
	char b[]="abc";
	fun1(a);
	fun2(b);
//	fun2(a);
	return 0;
	}
