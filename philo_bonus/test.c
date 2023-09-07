#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <semaphore.h>
#include "include/philo_bonus"

#define NUM_CHILD 5
#define TRUE 1
#define FALSE 0

int routine(t_philo *philo)
{

}

int main(int argc, char **argv)
{
	t_data *data;
	
	if (args_wrong(argc, argv) == TRUE)
		return (ft_pustr)







	pid_t pidC;
	int status;

	for (int i = 0; i < NUM_CHILD; i++)
	{
		pidC = fork();
		if (pidC > 0) //parent
			continue;
		else if (pidC == 0)//child
		{
			
			exit(0);
		}
		else
		{/*error*/};
	}
	for (int i = 0; i < NUM_CHILD; i++)
	{
		pidC = wait(&status);
		printf("PADRE PID = %d | PID child %d stopped | status child %d\n", getpid(), pidC, status);
	}
	return (0);
}
