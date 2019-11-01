#include <iostream>
#include <signal.h>
#include <sys/types.h>
void handler(int sig)
{
	switch(sig)
	{
		case 2:
			std::cout <<"catch sig"<< sig << std::endl;
			break;
		case 3:
			std::cout <<"catch sig" << sig << std::endl;
			break;
		default:
			break;
	}
}
int main()
{
	signal(3,handler);//对3号信号处理
	struct sigaction act, oact;
	act.sa_handler=handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags=0;
	sigaction(2,&act,&oact);
	while(1);

	return 0;
}
