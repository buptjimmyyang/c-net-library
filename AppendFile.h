#ifndef __APPENDFILE__
#define __APPENDFILE__
#include<string>
#include<string.h>
class AppendFile
{
public:
	explicit AppendFile(std::string filename);
	~AppendFile();
	void append(const char *log,const size_t len);

	void Flush();
	size_t writtenBytes() const{return writtenBytes_;}

private:
	size_t write(const char *logline,size_t len);
	FILE *fp_;
	char buffer_[64*1024];
	size_t writtenBytes_;
};
#endif
