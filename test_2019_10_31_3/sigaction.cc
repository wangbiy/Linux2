#include <iostream>
#include <signal.h>
#include <sys/types.h>
void handler(int sig)
{
	std::cout <<"catch sig"<< sig << std::endl;
}
int main()
{
	struct sigaction act, oact;
	act.sa_handler=handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags=0;
	sigaction(2,&act,&oact);
	while(1);

	return 0;
}
