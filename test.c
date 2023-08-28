#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

# define RESET  		"\x1B[0m"
# define RED  			"\x1B[31m"
# define GREEN	  		"\x1B[32m"
# define YELLOW  		"\x1B[33m"
# define BLUE 			"\x1B[34m"
# define MAGENTA 		"\x1B[35m"
# define CYAN  			"\x1B[36m"
# define WHITE  		"\x1B[37m"
# define ORANGE			"\x1b[38;5;209m"

size_t	current_time(void)
{
	struct timeval	time;
	size_t			current_time;

	gettimeofday(&time, NULL);
	current_time = (time.tv_sec) * 1000 + (time.tv_usec) / 1000;
	return (current_time);
}

/* int ft_usleep(useconds_t microseconds)
{
	int i;

	i = -1;
	if (microseconds < 0)
		return (-1);
	while (++i * 10 <= microseconds)
		usleep(10);
	return (0);
} */
void	ft_usleep(size_t time)
{
	size_t	start;

	start = current_time();
	while (current_time() < start + time)
		usleep(10);
}

int main()
{
	size_t	started = current_time();
	size_t	eat_time = 200 * 1000;

	/* while (1)
	{
		usleep(eat_time * 1000);
		printf("%ld\n", current_time() - started);
	} */
	while (1)
	{
		ft_usleep(eat_time);
		printf("%ld\n", current_time() - started);
	}
	return 0;
	int i = -1;
	while (++i < 50)
	{
		size_t startTime = current_time() * 1000;
		printf("Before TIME: %lu\n", startTime);
		usleep(1000);
		size_t endTime = current_time() * 1000;
		printf("After  TIME: %lu\n", endTime);
		if (endTime - startTime == 2000)
			printf(RED"Time spent: %lu\n"RESET, endTime - startTime);
		else
			printf("Time spent: %lu\n", endTime - startTime);

	}
	return (0);
}