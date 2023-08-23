/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:44:27 by glacroix          #+#    #+#             */
/*   Updated: 2023/08/23 19:43:28 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	mutex_init(t_data *data)
{
	int	i;

	i = -1;
	data->ready_set = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(data->ready_set, NULL);
 	data->forks = malloc(sizeof(*data->forks) * data->nbr_philos);
	while (++i < data->nbr_philos)
		pthread_mutex_init(&data->forks[i], NULL);
}

void	args_init(int argc, char **argv, t_data *data)
{
	data->nbr_philos = ft_atoi(argv[1]);
	data->start_time = get_time();
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->max_eating_cycles = ft_atoi(argv[5]);
	else
		data->max_eating_cycles = ft_atoi("-1");
	mutex_init(data);
}

int	threads_init(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = -1;
	philo = malloc(sizeof(*philo) * data->nbr_philos);
	pthread_mutex_lock(data->ready_set);
	while (++i < data->nbr_philos)
	{
		philo[i].id = i + 1;
		philo[i].data = data;
		philo[i].has_ate_n_times = 0;
		philo->flag_max_meals = 0;
		philo[i].dead = FALSE;
		if (pthread_create(&philo[i].thread, NULL, (void *) routine, philo + i))
			return (printf("Error when creating thread\n"), 1);
	}
	pthread_mutex_unlock(data->ready_set);
	i = 0;
	//!TODO implement philo death variable inside main thread
/* 	while (philo[i].dead == FALSE && i < data->nbr_philos - 1)
	{
		if (philo_died(philo + i) == 1)
			philo[i].dead = TRUE;
		i++;
	} */
	/* for (int i = 0; i < data->nbr_philos; i++)
	{
		if (philo[i].dead == TRUE)
		{
			for (int j = 0; j < data->nbr_philos; j++)
				pthread_detach(philo[j].thread);
		}
	} */
	i = -1;
	while (++i < data->nbr_philos)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
			return (printf("Error when joining thread\n"), 1);
	}
	pthread_mutex_destroy(data->forks);
	return (0);
}
