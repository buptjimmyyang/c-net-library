#include"../LogStream.h"
#include<iostream>
#include<string>
using namespace std;
int main()
{
	LogStream log;
	log<<-22222222;
	const LogStream::Buffer& buf=log.buffer();
	cout<<"test int"<<buf.toString()<<endl;
	log<<true;
	cout<<"test bool"<<buf.toString()<<endl;
	log<<1.22;
	cout<<"test double "<<buf.toString()<<endl;
	
	log<<"hello";
	cout<<"test char "<<buf.toString()<<endl;
	string a("world");
	cout<<"test string "<<buf.toString()<<endl;
return 1;
	}
