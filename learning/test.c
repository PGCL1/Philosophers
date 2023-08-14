#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

int mails = 0;
int lock = 0;
pthread_mutex_t mutex;


//trying to run a rolling dice function with 4 threads and returning a value from pthread_join function
void *routine()
{
		int	value = (rand() % 6) + 1;
		int* res = malloc(sizeof(int));
		
		*res = value;
		printf("Before: Address from result is %p\n", res);
		return (void*) res;
}

int main(int argc, char **argv)
{
	int i;
	int* res;
	srand(time(NULL));
	pthread_t philo;
	//creating the threads
	if (pthread_create(&philo, NULL, &routine, NULL) != 0)
		return 1;
	//waiting for the threads' execution end
	if (pthread_join(philo, (void**) &res) != 0)
		return 1;
	printf("AFTER: Address from result is %p\n", res);
	printf("AFTER: Result from rolling is %d\n", *res);
	return(0);	
}