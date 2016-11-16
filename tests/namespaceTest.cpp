#include<iostream>
using namespace std;
namespace yang{
class test{
	public:
	test(){
		}
	void getOut(){
		
		cout<<"test out"<<endl;
		}
	};

}
namespace yang {
	class test;
	}
int main(){
	yang::test t;
	t.getOut();
	return 0;
	}
