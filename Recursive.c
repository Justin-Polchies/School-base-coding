//Justin Polchies

#include <stdio.h>

int repeat(int n);

int main() {
	int n = 1;
	repeat(n);
	return 0;
}

//A recursive function that will never get to the base case to finish.
int repeat(int n) {

	if (n == 0) {
		return 0;
	}
	else {
		printf("%d\n", n);
		return repeat(n + 1);
	}
}
