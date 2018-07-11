#include <stdio.h>
#include <string.h>

struct Person {
   	char name[50];
	int id;
   	struct Address {
		char street[50];
		int postcode;
   	} address;
};

int main() {
   	struct Person a;
   	struct Person b;

	strcpy(a.name, "Adam");
	a.id = 123456;
	strcpy(a.address.street, "Jalan Inti");
	a.address.postcode = 223;

	printf("a.name: %s\n", a.name);
	printf("a.id: %d\n", a.id);
	printf("a.address.street: %s\n", a.address.street);
	printf("a.address.postcode: %d\n", a.address.postcode);
}
