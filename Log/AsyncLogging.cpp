#include"AsyncLogging.h"
#include"LogFile.h"
#include"Timestamp.h"

#include<stdio.h>

AsyncLogging::AsyncLogging(const std::string &basename,size_t rollSize,int flushInterval):flushInterval_(flushInterval),running_(false),rollSize_(rollSize),latch_(1),mutex_(),cond_(mutex_),currentBuffer_(new Buffer),nextBuffer_(new Buffer),buffers_()
{
	buffers_.reserve(16);
}

void AsyncLogging::append(const char *logline,int len)
{
	MutexLockGuard lock(mutex_);
	if(currentBuffer_->avail()>len)
		currentBuffer_->append(logline,len);
	else
	{
		buffers_.push_back(std::unique_ptr<Buffer>(currentBuffer_.release()));

		if(nextBuffer_)
			currentBuffer_=std::move(nextBuffer_);
		else
			currentBuffer_.reset(new Buffer);

		currentBuffer_->append(logline,len);
		cond_.notify();
	}
	
}

void AsyncLogging::threadFunc()
{
	
	latch_.countDown();
	
	LogFile output(basename_,rollSize_,false);

	BufferPtr newBuffer1(new Buffer);
	BufferPtr newBuffer2(new Buffer);

	BufferVector buffersToWrite;
	buffersToWrite.reserve(16);

	while(running_)
	{
	
//	cout<<"func running"<<endl;
		{
			MutexLockGuard lock(mutex_);
			if(buffers_.empty())
				cond_.waitForSeconds(flushInterval_);

			buffers_.push_back(std::unique_ptr<Buffer>(currentBuffer_.release()));
			currentBuffer_=std::move(newBuffer1);
			buffersToWrite.swap(buffers_);

			if(!nextBuffer_)
				nextBuffer_=std::move(newBuffer2);
		}	

		if(buffersToWrite.size()>25)
		{
			char buf[256];
			snprintf(buf,sizeof(buf),"Dropped log messages at %s,%zd larger buffers\n",Timestamp::now().toFormattedString().c_str(),buffersToWrite.size()-2);
			fputs(buf,stderr);
			output.append(buf,static_cast<int>(strlen(buf)));
			buffersToWrite.erase(buffersToWrite.begin()+2,buffersToWrite.end());
		}

		for(int i=0;i<buffersToWrite.size();++i)
			output.append(buffersToWrite[i]->data(),buffersToWrite[i]->length());
		if(buffersToWrite.size()>2)
			buffersToWrite.resize(2);

		if(!newBuffer1)
		{
			newBuffer1=std::move(buffersToWrite.back());
			buffersToWrite.pop_back();
			newBuffer1->reset();
		}

		if(!newBuffer2)
		{
			newBuffer2=std::move(buffersToWrite.back());
			buffersToWrite.pop_back();
			newBuffer2->reset();
		}

		buffersToWrite.clear();
		output.flush();
	}
	output.flush();
}
