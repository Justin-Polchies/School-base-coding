#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>


int main() {

	fork();
	fork();

	int pid = getpid();
	printf("Current PID #: %d\n", pid);
	return 0;
}