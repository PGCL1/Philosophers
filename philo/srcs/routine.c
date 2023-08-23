/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 18:13:29 by glacroix          #+#    #+#             */
/*   Updated: 2023/08/23 18:43:24 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int philo_died(t_philo *philo)
{
	if (TIME_SPENT >= TIME_TO_DIE)
	{
		printf(YELLOW"%ld %d died\n"RESET, TIME_SPENT, philo->id);
		return (1);
	}
	return (0);
}

void	takeforks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[LEFT]);
	pthread_mutex_lock(&philo->data->forks[RIGHT]);
	printf(WHITE"%ld %d has taken a fork\n"RESET, TIME_SPENT, philo->id);
	printf(WHITE"%ld %d has taken a fork \n"RESET, TIME_SPENT, philo->id);
}

void	eat(t_philo *philo)
{
	usleep(TIME_TO_EAT);
	printf(GREEN"%ld %d is eating\n"RESET, TIME_SPENT, philo->id);
	philo->has_ate_n_times++;
	if (philo->data->max_eating_cycles > -1
		&& philo->has_ate_n_times >= philo->data->max_eating_cycles)
		philo->flag_max_meals = TRUE;
	philo->last_meal_time = get_time() - philo->data->start_time;
	printf("last meal was at %lu\n", philo->last_meal_time);
}

void	putforks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->forks[LEFT]);
	pthread_mutex_unlock(&philo->data->forks[RIGHT]);
	if (philo->flag_max_meals == TRUE)
		return ;
	printf(ORANGE"%ld %d is sleeping\n"RESET, TIME_SPENT, philo->id);
	printf("time spent is %lu\n", TIME_SPENT);
	usleep(TIME_TO_SLEEP);
	printf(MAGENTA"%ld %d is thinking\n"RESET, TIME_SPENT, philo->id);
}

void	*routine(t_philo *philo)
{
	pthread_mutex_lock(philo->data->ready_set);
	pthread_mutex_unlock(philo->data->ready_set);
	if (philo->id % 2 == 0)
		usleep(200);
	while (1)
	{
		if (philo->data->max_eating_cycles == 0)
			break ;
		takeforks(philo);
		eat(philo);
		putforks(philo);
		if (philo->flag_max_meals == TRUE)
			break ;
	}
	return (NULL);
}
