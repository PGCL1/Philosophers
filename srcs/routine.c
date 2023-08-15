/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 18:13:29 by glacroix          #+#    #+#             */
/*   Updated: 2023/08/15 18:47:36 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

//timestamp_in_ms X has taken a fork

static void pick_up_left_fork(t_philo *philo)
{
	printf("%d\n", philo->has_left_fork);
	pthread_mutex_lock(&philo->data->forks);
	philo->has_left_fork = 1;
	printf(GREEN"%ld %d has taken a left fork\n"RESET, get_time(), philo->id);
	pthread_mutex_unlock(&philo->data->forks);
	printf("here\n");
}

static void pick_up_right_fork(t_philo *philo)
{
	printf("%d\n", philo->has_right_fork);
	pthread_mutex_lock(&philo->data->forks);
	philo->has_right_fork = 1;
	printf(GREEN"%ld %d has taken a right fork\n"RESET, get_time(), philo->id);
	pthread_mutex_unlock(&philo->data->forks);
}

void* routine(t_philo *philo) 
{
	while (1)
	{
		if (!philo->has_left_fork)
			pick_up_left_fork(philo);
		if (!philo->has_right_fork)
			pick_up_right_fork(philo);
		else
			break;
	}
	return NULL;
}
