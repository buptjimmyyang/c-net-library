#include"LogFile.h"
#include<stdio.h>
#include<time.h>
#include<unistd.h>
//get process id
pid_t pid()
{
	return getpid();	
}
//get hostname
std::string hostname()
{
	char buf[256];
	if(gethostname(buf,sizeof(buf))==0)
	{
	return buf;
	
}
	else{
			return "unknownhost";
		}
}
LogFile::LogFile(const std::string &basename,size_t rollSize,bool threadSafe,int flushInterval,int checkEveryN):basename_(basename),rollSize_(rollSize),flushInterval_(flushInterval),checkEveryN_(checkEveryN),count_(0),mutex_(threadSafe?new MutexLock():NULL),startOfPeriod_(0),lastRoll_(0),lastFlush_(0){
	
	rollFile();
	}
bool LogFile::rollFile()
{
	time_t now=0;
	std::string filename=getLogFileName(basename_,&now);
	time_t start=now/kRollPerSeconds_*kRollPerSeconds_;

	if(now>lastRoll_)
	{
		lastRoll_=now;
		lastFlush_=now;
		startOfPeriod_=start;
		file_.reset(new AppendFile(filename));	
		return true;
	}
	return false;
}
std::string LogFile::getLogFileName(const std::string &basename,time_t *now)
{
	std::string filename;
	filename.reserve(basename.size()+64);
	filename=basename;

	char timebuf[32];
	struct tm tm;
	*now =time(NULL);
	gmtime_r(now,&tm);
	strftime(timebuf,sizeof(timebuf),".%Y%m%d-%H%M%S.",&tm);
	filename+=timebuf;

	filename+=hostname();
	
	char pidbuf[32];
	snprintf(pidbuf,sizeof(pidbuf),".%d",pid());

	filename+=pidbuf;
	filename+=".log";
	return filename;
}

LogFile::~LogFile()
{}

void LogFile::append(const char *logline,int len)
{
	if(mutex_){
	MutexLockGuard lock(*mutex_);	
	append_unlocked(logline,len);	
	}	
	else{
		
		append_unlocked(logline,len);
		}
	
}

void LogFile::flush()
{
	if(mutex_){
		MutexLockGuard lock(*mutex_);
		file_->Flush();
		}
	else{
		file_->Flush();
		}
	
}

void LogFile::append_unlocked(const char *logline,int len)
{
	file_->append(logline,len);
	if(file_->writtenBytes()>rollSize_)
		rollFile();
	else{
		++count_;
		if(count_>=checkEveryN_){
			count_=0;
			time_t now=time(NULL);
			time_t thisPeriod=now/kRollPerSeconds_*kRollPerSeconds_;
			if(thisPeriod!=startOfPeriod_)
				rollFile();
			else if(now - lastFlush_>flushInterval_){
				
				lastFlush_=now;
				file_->Flush();
				}
		}
		
	}
}
