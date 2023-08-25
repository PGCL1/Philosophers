/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:44:27 by glacroix          #+#    #+#             */
/*   Updated: 2023/08/25 21:12:05 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//changes : line 61

#include "../include/philo.h"

static void	*mutex_init(t_data *data)
{
	int	i;

	i = -1;
	//data->ready_set = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(&data->ready_set, NULL);
 	data->forks = malloc(sizeof(*data->forks) * data->nbr_philos);
	if (!data->forks)
		return (printf("data->forks malloc failed\n"), (int*)1);
	while (++i < data->nbr_philos)
		pthread_mutex_init(&data->forks[i], NULL);
	return NULL;
}

void	args_init(int argc, char **argv, t_data *data)
{
	data->nbr_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->max_eating_cycles = ft_atoi(argv[5]);
	else
		data->max_eating_cycles = -1;
	if ((int) mutex_init(data) == 1)
		return;
}

int	threads_init(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = -1;
	philo = malloc(sizeof(*philo) * data->nbr_philos);
	if (!philo)
		return (1);
	pthread_mutex_lock(&data->ready_set);
	while (++i < data->nbr_philos)
	{
		philo[i].id = i + 1;
		philo[i].data = data;
		philo[i].has_ate_n_times = 0;
		philo[i].flag_max_meals = 0;
		philo[i].dead = FALSE;
		philo[i].finished_eating_time = 0;
		if (pthread_create(&philo[i].thread, NULL, (void *) routine, philo + i))
			return (printf("Error when creating thread\n"), 2);
	}
	data->start_time = current_time();
	pthread_mutex_unlock(&data->ready_set);
	//!TODO implement philo death variable inside main thread
 	while (1)
	{
		for (int i = 0; i < data->nbr_philos; i++)
		{
			philo_died(&(philo[i]));
			if (philo[i].dead == TRUE)
			{
				printf(RED"ID: %d | %lu died//\n"RESET, philo[i].id,  current_time() - philo->data->start_time);
				printf(RED"ID: %d | %lu died//\n"RESET, philo[i].id,  philo[i].start_time);
				printf("he died\n");
	/* 			exit(0); */
			}
		}
	} 
	i = 0;
	while (i < data->nbr_philos)
	{
		if (pthread_join(philo[i++].thread, NULL) != 0)
			return (printf("Error when joining thread\n"), 3);
	}
	pthread_mutex_destroy(data->forks);
	return (0);
}
