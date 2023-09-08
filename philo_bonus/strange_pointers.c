#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <semaphore.h>
//#include "include/philo_bonus"

#define NUM_CHILD 5
#define TRUE 1
#define FALSE 0

typedef struct something {
	const char *name;
	int age;
} 				something;

void	leaks()
{
	system("leaks -q main");
}

int	main(void)
{
	atexit(leaks);
	char *name;

	name = malloc(sizeof(char) * 5);
	name = "test";

	printf("name: %s\n", name);
	//name = "Guillaume";
	for (int i = 0; name[i]; i++)
	{
		printf("[%c]\n", name[i]);
	}
	printf("name: %s\n", name);
	return 0;
	name[0] = 't';
	name[1] = 'e';
	name[2] = 's';
	name[3] = 't';
	name[4] = '\0';
	printf("%s\n", name);
	name[0] = 'a';
	printf("%s\n", name);
}
