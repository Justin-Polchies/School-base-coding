#include <stdio.h>

int main() {

	FILE theFile;
	char ch;

	theFile = fopen();

	if (theFile == null) {
		printf("File does not Exist\n");

	}
	else {
		while (ch != EOF) {
			ch = fgetc(theFile);
			printf("%c", ch);
			usleep(1000);
		}
	}

	return 0;
}
