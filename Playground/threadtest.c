// compile with -lpthread
#include <stdio.h>
#include <pthread.h>
#include <string.h>

// int pthread_create(pthread_t* child, pthread_attr_t* attr, void* (*fn)(void*), void* arg);
// int pthread_create(pthread_t* child, NULL,  void* (*fn)(void*), NULL);

struct argstruct {
	int id;
	char name[128];
};

void *Child_Fn(void *arg) {
	struct argstruct *myarg = arg;
	int num = myarg->id;
	char myname[128];
	strcpy(myname, myarg->name);
	printf("Child received id: %d\n", num);
	printf("Child received name: %s\n", myname);
	return NULL;
}

int main() {
	struct argstruct arg;
	arg.id = 1;
	strcpy(arg.name, "apple");

       	pthread_t tchild;
	
	// NULL is attr: what resources is shared with parent
	if (pthread_create(&tchild, NULL, &Child_Fn, &arg) != 0) {
		perror("Failed to create thread");
	}

	pthread_join(tchild, NULL);

 	return 0;
}
