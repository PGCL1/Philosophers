/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 18:13:29 by glacroix          #+#    #+#             */
/*   Updated: 2023/08/24 18:42:47 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/* void philo_died(t_philo *philo)
{
	if (philo->finished_eating_time != 0)
	{
		if (philo->finished_eating_time - philo->start_time >= philo->data->time_to_die)
			{
				printf("ID: %d | %lu died\n", philo->id, philo->finished_eating_time - philo->start_time);
			}
	}
	else if (philo->start_time >= philo->data->time_to_die)
		printf("ID: %d | %lu died\n", philo->id, philo->finished_eating_time - philo->start_time);
} */


void	takeforks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->id-1]);
	/* printf(WHITE"%ld %d has taken a fork\n"RESET, get_time() - philo->data->start_time, philo->id); */
	pthread_mutex_lock(&philo->data->forks[philo->id % philo->data->nbr_philos]);
	/* printf(WHITE"%ld %d has taken a fork \n"RESET, get_time() - philo->data->start_time, philo->id); */
	/* philo->end_pick_time = get_time() - philo->data->start_time - (philo->has_ate_n_times * philo->data->time_to_sleep + philo->has_ate_n_times * philo->data->time_to_eat);
	printf("%d time spent between pick up time and last cycle is %lu\n", philo->id, philo->end_pick_time); */
}

void	eat(t_philo *philo)
{
	/* printf(GREEN"%ld %d is eating\n"RESET, get_time() - philo->data->start_time, philo->id); */
	usleep(philo->data->time_to_eat * 1000);
	philo->has_ate_n_times++;
	if (philo->data->max_eating_cycles > -1
		&& philo->has_ate_n_times >= philo->data->max_eating_cycles)
		philo->flag_max_meals = TRUE;
	philo->finished_eating_time = get_time() - philo->data->start_time;
	/*printf("%d time spent between take and eat is %lu\n", philo->id, philo->finished_eating_time - philo->end_pick_time); */
}

void	putforks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->forks[philo->id-1]);
	pthread_mutex_unlock(&philo->data->forks[philo->id % philo->data->nbr_philos]);
	if (philo->flag_max_meals == TRUE)
		return ;
	/* printf(ORANGE"%ld %d is sleeping\n"RESET, get_time() - philo->data->start_time, philo->id); */
	usleep(philo->data->time_to_sleep * 1000);
	/* printf(MAGENTA"%ld %d is thinking\n"RESET, get_time() - philo->data->start_time, philo->id); */
	/* philo->end_put_time = get_time() - philo->data->start_time;
	printf("%d time spent between eat and put is %lu\n", philo->id, philo->end_put_time - philo->finished_eating_time); */
}

void	*routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->ready_set);
	pthread_mutex_unlock(&philo->data->ready_set);
	if (philo->id % 2 == 0)
		usleep(200);
	while (1)
	{
		philo->start_time = get_time() - philo->data->start_time;
		if (philo->data->max_eating_cycles == 0)
			break ;
		takeforks(philo);
		eat(philo);
		putforks(philo);
		if (philo->flag_max_meals == TRUE)
			break ;
		printf("ID: %d | ate %d | time since last meal: %lu\n", philo->id, philo->has_ate_n_times, philo->finished_eating_time - philo->start_time);
		if (philo->finished_eating_time - philo->start_time >= philo->data->time_to_die)
		{
			printf(RED"ID: %d | %lu died\n"RESET, philo->id, philo->finished_eating_time - philo->start_time);
			philo->dead = TRUE;
		}
	}
	return (NULL);
}
