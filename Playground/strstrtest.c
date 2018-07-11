#include <string.h>
#include <stdio.h>

int main() {
	char s[] = "this is an apple";
	if (strstr(s,"apples") != NULL) {
		printf("found\n");
	} else {
		printf("not found\n");
	}
}
