/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 18:13:29 by glacroix          #+#    #+#             */
/*   Updated: 2023/08/22 19:34:02 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

//timestamp_in_ms X has taken a fork


void takeforks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[LEFT]);
	pthread_mutex_lock(&philo->data->forks[RIGHT]);
	printf(ORANGE"%ld %d has taken a left fork\n"RESET, TIME_SPENT, philo->id);
	printf(ORANGE"%ld %d has taken a right fork \n"RESET, TIME_SPENT, philo->id);
	
}

void eat(t_philo *philo)
{
	usleep(TIME_TO_EAT);
	printf(GREEN"%ld %d is eating\n"RESET, TIME_SPENT, philo->id);
}

void putforks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->forks[LEFT]);
	pthread_mutex_unlock(&philo->data->forks[RIGHT]);
	usleep(TIME_TO_SLEEP);
}

void *routine(t_philo *philo)
{
	pthread_mutex_lock(philo->data->start_same_time);
	pthread_mutex_unlock(philo->data->start_same_time);
	if (philo->id % 2 == 0)
		usleep(200);
	while (1)
	{
		takeforks(philo);
		eat(philo);
		putforks(philo);
	}
	return (NULL);
}
