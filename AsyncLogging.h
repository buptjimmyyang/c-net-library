#ifndef __ASYNCLOGGING__
#define __ASYNCLOGGING__
#include"Mutex.h"
#include<thread>
#include"LogStream.h"
#include"CountDownLatch.h"
#include<memory>
#include<utility>
#include<vector>
#include<functional>
#include<iostream>
using namespace std;
class AsyncLogging
{
private:
AsyncLogging(const AsyncLogging&);
void operator=(const AsyncLogging&);

void threadFunc();

typedef FixedBuffer<kLargeBuffer> Buffer;
typedef std::vector<std::unique_ptr<Buffer>> BufferVector;
typedef std::unique_ptr<Buffer> BufferPtr;

const int flushInterval_;
bool running_;

std::string basename_;
size_t rollSize_;
std::thread thread_;

CountDownLatch latch_;

MutexLock mutex_;
Condition cond_;

BufferPtr currentBuffer_;
BufferPtr nextBuffer_;
BufferVector buffers_;

public:
AsyncLogging(const std::string &basename,size_t rollSize,int flushInterval=3);

~AsyncLogging()
{
	if(running_)
		stop();
}
void append(const char *longline,int len);
void start()
{
	running_=true;
	thread_=std::move(std::thread(std::bind(&AsyncLogging::threadFunc,this)));
	cout<<"move h"<<endl;
	latch_.wait();
	cout<<"wait h"<<endl;

}

void stop()
{
	running_=false;
	cond_.notify();
	thread_.join();
}
};
#endif
