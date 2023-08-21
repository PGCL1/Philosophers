/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:44:27 by glacroix          #+#    #+#             */
/*   Updated: 2023/08/21 15:40:07 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	args_init(int argc, char **argv, t_data *data)
{
	data->nbr_philos = atoi(argv[1]);
	data->start_time = get_time();
	data->time_to_die = atoi(argv[2]);
	data->time_to_eat = atoi(argv[3]);
	data->time_to_sleep = atoi(argv[4]);
	if (argc == 6)
		data->max_eating_cycles = atoi(argv[5]);
}

int	threads_init(t_data *data)
{
	t_philo	*philo;
	
	//!TODO: change calloc to ft_calloc
	philo = calloc(sizeof(*philo), data->nbr_philos);
 	data->forks = calloc(sizeof(pthread_mutex_t**), data->nbr_philos);
	//! problem with pointer to pointer related to mutex_lock in routine - the mutex didn't lock
	pthread_mutex_init((data->forks), NULL);
	printf("did it work mutex init: %d\n", pthread_mutex_init(data->forks, NULL));
	exit(0);
	for (int i = 0; i < data->nbr_philos; i++)
	{
		philo[i].id = i + 1;
		philo[i].data = data;
		if (pthread_create(&philo[i].thread, NULL, (void *) routine, philo + i) != 0)
			return (printf("Error when creating thread\n"), 1);
		else 
			printf("Succes\n");
	}
	while(1);
	for (int i = 0; i < data->nbr_philos; i++)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
			return (printf("Error when joing thread\n"), 1);
	}
	pthread_mutex_destroy((*data->forks));
	return (0);
}

