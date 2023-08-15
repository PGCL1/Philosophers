/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:44:27 by glacroix          #+#    #+#             */
/*   Updated: 2023/08/15 17:33:03 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	args_init(int argc, char **argv, t_data *data)
{
	struct timeval	time;
	size_t			current_time;

	memset(data, 0, sizeof(t_data));
	//getting the number of philos
	data->nbr_philos = atoi(argv[1]);
	printf("There are %d philos\n", data->nbr_philos);

	//TODO: getting the current time -- put in separate function
	gettimeofday(&time, NULL);
	current_time = (time.tv_sec) * 1000 + (time.tv_usec) / 1000;
	printf("current time is %ld\n", current_time);

	//getting the time_to_die arg
	data->time_to_die = atoi(argv[2]);
	printf("time_to_die is %ld\n", data->time_to_die);

	//getting the time_to_eat arg
	data->time_to_eat = atoi(argv[3]);
	printf("time_to_eat is %ld\n", data->time_to_eat);

	//getting the time_to_sleep arg
	data->time_to_sleep = atoi(argv[4]);
	printf("time_to_sleep is %ld\n", data->time_to_sleep);

	data->test = 0;
	//getting the max cycles if argc == 6
	if (argc == 6)
	{
		data->max_eating_cycles = atoi(argv[5]);
		printf("max_eating_cycles are %d\n", data->max_eating_cycles);
	}
}


void* routine(t_philo *philo) {
	while (1)
	{
		pthread_mutex_lock(&philo->data->forks);
		philo->data->test++;
		printf("Address of data: %p\nAddress of data.test: %p\n", philo->data, &philo->data->test);
		sleep(1);
		pthread_mutex_unlock(&philo->data->forks);
	}
	return NULL;
}

int	philos_init(t_data *data)
{
	t_philo philo[data->nbr_philos];
	pthread_mutex_init(&data->forks, NULL);

	for (int i = 0; i < data->nbr_philos; i++)
	{
		philo[i].id = i + 1;
		philo[i].data = data;
		if (pthread_create(&philo[i].thread, NULL, (void *)routine, philo + i) != 0)
			return (printf("Error when creating thread\n"), 1);
	}
	for (int i = 0; i < data->nbr_philos; i++)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
			return (printf("Error when joing thread\n"), 1);
	}
	pthread_mutex_destroy(&data->forks);
	return (0);
}
