#include"../AsyncLogging.h"
#include"../Logging.h"
#include"../Timestamp.h"
#include<stdio.h>
#include<sys/resource.h>
#include<sys/types.h>
#include<unistd.h>
#include<iostream>
using namespace std;
int kRollSize=500;
AsyncLogging *g_asyncLog=NULL;

void asyncOutput(const char *msg,int len)
{
	g_asyncLog->append(msg,len);
}

int main()
{
//Logger::setOutput(asyncOutput);
cout<<"set main"<<endl;

AsyncLogging log("async",kRollSize);
log.start();
g_asyncLog=&log;
Logger::setOutput(asyncOutput);
//cout<<"log start main"<<endl;
for(int i=0;i<20000;++i)
	LOG_INFO<<"hello ";

//cout<<"info"<<endl;
while(1);
return 0;

}
