/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:44:27 by glacroix          #+#    #+#             */
/*   Updated: 2023/09/01 20:46:32 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//changes : line 61

#include "../include/philo.h"

static void	*mutex_init(t_data *data)
{
	int	i;

	i = -1;
	pthread_mutex_init(&data->ready_set, NULL);
	pthread_mutex_init(&data->log_mutex, NULL);
	pthread_mutex_init(&data->death_mutex, NULL);
	pthread_mutex_init(&data->finished_eating_mutex, NULL);
	pthread_mutex_init(&data->max_eat_mutex, NULL);
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
	data->philo_died = FALSE;
	data->log = TRUE;
	data->exit_flag = 0;
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
	int		stop;

	i = -1;
	stop = 0;
	philo = malloc(sizeof(*philo) * data->nbr_philos);
	if (!philo)
		return (1);
	pthread_mutex_lock(&data->ready_set);
	while (++i < data->nbr_philos)
	{
		philo[i].id = i + 1;
		philo[i].data = data;
		philo[i].ate_count = 0;
		philo[i].ate_enough = FALSE;
		philo[i].finished_eating_time = 0;
		if (pthread_create(&philo[i].thread, NULL, (void *) schedule, philo + i))
			return (printf("Error when creating thread\n"), 2);
	}
	
	data->start_time = current_time();
	pthread_mutex_unlock(&data->ready_set);
	while (!stop)
	{
		for (int i = 0; i < data->nbr_philos; i++)
		{
			pthread_mutex_lock(&philo->data->max_eat_mutex);
			if (data->exit_flag == data->nbr_philos)
			{
				pthread_mutex_unlock(&philo->data->max_eat_mutex);
				stop = 1;
				break;
			}
			pthread_mutex_unlock(&philo->data->max_eat_mutex);
			philo_died(&philo[i]);
			if (philo->data->philo_died == 1 && data->exit_flag != data->nbr_philos)
			{
				printf(/* RED */"%llu %d died\n"/* RESET */,  current_time() - philo->data->start_time, philo[i].id);
				stop = 1;
				pthread_mutex_lock(&philo->data->log_mutex);
				data->log = FALSE;
				pthread_mutex_unlock(&philo->data->log_mutex);
				break;
			}
		}
	} 
	i = -1;
	while (++i < data->nbr_philos)
	{
		//int err = pthread_join(philo[i].thread, NULL);
		if (pthread_join(philo[i].thread, NULL) != 0)
			return (printf("Error when joining thread\n"), 3);
		/*  else
			printf(RED"%llu %d was joined\n"RESET, current_time() - philo->data->start_time, philo[i].id);  */
	}
	pthread_mutex_unlock(data->forks);
	pthread_mutex_destroy(data->forks);
	return (0);
}

/*
1 800 200 200
a philo should die
4 310 200 100
a philo should die
4 200 205 200
a philo should die
5 800 200 200 7
no one should die, simulation should stop after 7 eats
4 410 200 200 10
no one should die, simulation should stop after 10 eats
-5 600 200 200
should error and not run (no crashing)
4 -5 200 200
should error and not run (no crashing)
4 600 -5 200
should error and not run (no crashing)
4 600 200 -5
should error and not run (no crashing)
4 600 200 200 -5
should error and not run (no crashing)
//--------------------------------------------
5 800 200 200
no one should die
5 600 150 150
no one should die
4 410 200 200
no one should die
100 800 200 200
no one should die
105 800 200 200
no one should die
200 800 200 200
no one should die



*/