#include<string>
#include<unistd.h>
#include<iostream>
#include<netdb.h>
#include<arpa/inet.h>
using namespace std;
std::string hostname()
{
		char buf[256];
			/*if(gethostname(buf,sizeof(buf)==0))
					{
			//cout<<buf<<endl;
			buf[sizeof(buf)-1]='\0';
			cout<<buf<<endl;
			return buf;
					}
			else{
				return "unknownhost";
				}*/
if(gethostname(buf,sizeof(buf))!=0)
	return "unknow name";
else
	return buf;
/*	struct hostent *host;
		//char addr_p[256];
		if((host=gethostent())==NULL)
			return "unknown";
		return host->h_name;
*/
}
int main()
{
	
	cout<<hostname()<<endl;
	return 0;
	}
