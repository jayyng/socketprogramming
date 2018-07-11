#include <stdio.h>
#include <string.h>


struct Person {
	int id;
	char name[50];
};

void changedata(int, char* , struct Person* );

int main() {
	struct Person person;
	changedata(23, "John", &person);

	printf("person.id: %d\n", person.id);
	printf("person.name: %s\n", person.name);
}


void changedata(int i, char* n, struct Person* p) {
	p->id = i;
	strcpy(p->name, n);
}
