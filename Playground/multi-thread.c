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
	struct argstruct arg,arg2;
	arg.id = 1;
	strcpy(arg.name, "apple");
	
	arg2.id = 2;
	strcpy(arg2.name, "ball");

       	pthread_t tchild, tchild2;
	
	// NULL is attr: what resources is shared with parent
	if (pthread_create(&tchild, NULL, &Child_Fn, &arg) != 0) {
		perror("Failed to create thread");
	}


	if (pthread_create(&tchild2, NULL, &Child_Fn, &arg2) != 0) {
		perror("Failed to create thread2");
	}

	
	pthread_join(tchild, NULL);
	pthread_join(tchild2,NULL);

 	return 0;
}
