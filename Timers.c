#include <stdio.h>
#include <sys/time.h>
#include <signal.h>


void TM(int signum) {
	struct timeval current;
	time_t t;
	struct tm* local;
	gettimeofday(&current, NULL);
	t = current.tv_sec;
	local = localtime(&t);

	printf("Current Time : %s\n",asctime(local));

}


int main() {

	struct itimerval timer;
	struct sigaction sig;

	memset(&sig, 0, sizeof(sig));
	sig.sa_handler = &TM;
	sigaction(SIGVTALRM, &sig, NULL);


	timer.it_value.tv_usec = 1000;
	timer.it_interval.tv_usec = 1000;



}