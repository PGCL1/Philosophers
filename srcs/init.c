/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:44:27 by glacroix          #+#    #+#             */
/*   Updated: 2023/08/22 19:30:30 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void mutex_init(t_data *data)
{
	int	i;

	i = -1;
	data->start_same_time = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(data->start_same_time, NULL);
 	data->forks = malloc(sizeof(*data->forks) * data->nbr_philos);
	printf("nbr philos: %d\n", data->nbr_philos);
	while (++i < data->nbr_philos)
		pthread_mutex_init(&data->forks[i], NULL);
}

void	args_init(int argc, char **argv, t_data *data)
{
	data->nbr_philos = atoi(argv[1]);
	data->start_time = get_time();
	data->time_to_die = atoi(argv[2]);
	data->time_to_eat = atoi(argv[3]);
	data->time_to_sleep = atoi(argv[4]);
	if (argc == 6)
		data->max_eating_cycles = atoi(argv[5]);
	mutex_init(data);
}

int	threads_init(t_data *data)
{
	t_philo	*philo;
	
	//!TODO: change calloc to ft_calloc
	philo = malloc(sizeof(*philo) * data->nbr_philos);
	pthread_mutex_lock(data->start_same_time);
	for (int i = 0; i < data->nbr_philos; i++)
	{
		philo[i].id = i + 1;
		philo[i].data = data;
		philo->has_left_fork = 0;
		philo->has_right_fork = 0;
		philo->has_ate = 0;
		if (pthread_create(&philo[i].thread, NULL, (void *) routine, philo + i) != 0)
			return (printf("Error when creating thread\n"), 1);
	}
	pthread_mutex_unlock(data->start_same_time);
	for (int i = 0; i < data->nbr_philos; i++)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
			return (printf("Error when joining thread\n"), 1);
	}
	pthread_mutex_destroy(data->forks);
	return (0);
}

