#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int arr[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void* routine(void* arg)
{
	int index = *(int*)arg;
	int sum = 0;
	for (int i = 0; i < 5; i++)
		sum += arr[index + i];
	*(int*)arg = sum;
	printf("thread sum is %d\n", sum);
	return (arg);
}



//trying to create two threads to split an array and sum up in each thread their respective half
//then in the main thread add up each threads' result
int main()
{
	pthread_t thread[2];
	int *result = 0;

	for (int i = 0; i < 2; i++)
	{
		int* size = malloc(sizeof(int));
		*size = i * 5;
		if (pthread_create(thread + i, NULL, (void*) routine, size) == 1)
			return (perror("Error while creating the threads\n"), 1);
	}

	int globalSum = 0;
	for (int i = 0; i < 2; i++)
	{
		if (pthread_join(thread[i], &result) == 1)
			return (perror("Error while joining the threads\n"), 2);
		globalSum += *result;
		free(result);
	}
	printf("global sum is %d\n", globalSum);
	return (0);
}