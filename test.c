
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>

int	sum = 0;
void* routine(void *arg) {
	while (1)
	{
		sum += 1;
		//philo->data->test += 1;
		printf("%d\n", sum);
		sleep(1);
	}
		/* philo->data->test++;
		printf("Address of data: %p\nAddress of data.test: %p\n", philo->data, &philo->data->test); */
	return NULL;
}

int main()
{
	pthread_t	threads[2];

	for (int i = 0; i < 2; i++)
	{
		pthread_create(threads + i, NULL, routine, NULL);
	}
	for (int i = 0; i < 2; i++)
	{
		pthread_join(threads[i], NULL);
	}
}