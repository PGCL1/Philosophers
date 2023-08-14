#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>


//create 10 threads each printing a unique prime number from the array and printing it to the screen
/* int arr[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
pthread_mutex_t mutex;

void* routine(int *num){

	pthread_mutex_lock(&mutex);
	printf("%d ", *num);
	pthread_mutex_unlock(&mutex);
	free(num);
	return NULL;
}

int main()
{
	pthread_t thread[10];
	pthread_mutex_init(&mutex, NULL);
	//creating each thread
	 for (int i = 0; i < 10; i++)
		pthread_create(thread + i, NULL, (void*) routine, arr + i);
	//or do this
	for (int i = 0; i < 10; i++)
	{
		int *num = malloc(sizeof(int));
		*num = arr[i];
		pthread_create(thread + i, NULL, (void *)routine, num);
	}

	//waiting for the execution to end for each thread
	for (int i = 0; i < 10; i++)
		pthread_join(thread[i], NULL);
	pthread_mutex_destroy(&mutex);
	return (0);
} */



void* routine(){
	while (1)
	{
		printf("Thread is alive\n");
	}
	return NULL;
}

int main()
{
	pthread_t thread[2];
	//creating each thread
	for (int i = 0; i < 2; i++)
	{
		pthread_create(thread + i, NULL, &routine, NULL);
		pthread_detach(thread[i]);
	}
	//waiting for the execution to end for each thread
	for (int i = 0; i < 2; i++)
		pthread_join(thread[i], NULL);
	return (0);
}
