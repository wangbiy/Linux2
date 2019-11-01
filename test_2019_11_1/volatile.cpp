#include <iostream>
#include <signal.h>
volatile bool quit =false;//全局变量
void handler(int sig)
{
	switch(sig)
	{
		case 2:
			quit=true;
			std::cout<<"catch signal"<<sig<<std::endl;
			break;
		default:
			break;
	}
}
int main()
{
	signal(2,handler);
	while(!quit);
	std::cout<<"while quit!"<<std::endl;
	return 0;
}
