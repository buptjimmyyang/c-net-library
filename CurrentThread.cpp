#include"CurrentThread.h"
#include<linux/unistd.h>
#include<stdio.h>
#include<sys/syscall.h>
#include<time.h>
#include<unistd.h>
#include"Timestamp.h"
__thread int t_cachedTid = 0;
  __thread char t_tidString[32];
  __thread int t_tidStringLength = 6;
  __thread const char* t_threadName = "unknown";
  pid_t gettid()
{
	//调用系统调用获取线程id
  return static_cast<pid_t>(syscall(SYS_gettid));
}

void cacheTid()
{
  if (t_cachedTid == 0)
  {
    t_cachedTid = gettid();
    t_tidStringLength = snprintf(t_tidString, sizeof t_tidString, "%5d ", t_cachedTid);
  }
}
bool isMainThread()
{
  return tid() == getpid();
}
void sleepUsec(int64_t usec)
{
  struct timespec ts = { 0, 0 };
  ts.tv_sec = static_cast<time_t>(usec / Timestamp::kMicroSecondsPerSecond);
  ts.tv_nsec = static_cast<long>(usec % Timestamp::kMicroSecondsPerSecond * 1000);
  nanosleep(&ts, NULL);
}
