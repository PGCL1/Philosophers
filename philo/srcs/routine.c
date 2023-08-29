/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 18:13:29 by glacroix          #+#    #+#             */
/*   Updated: 2023/08/28 17:06:09 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void philo_died(t_philo *philo)
{
	if (current_time() - philo->data->start_time - philo->finished_eating_time >= philo->data->time_to_die)
		philo->dead = TRUE;
}

void	takeforks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->id-1]);
	printf("%lld %d has taken a fork\n", current_time() - philo->data->start_time, philo->id);
	pthread_mutex_lock(&philo->data->forks[philo->id % philo->data->nbr_philos]);
	printf("%lld %d has taken a fork \n", current_time() - philo->data->start_time, philo->id);
	philo->finished_eating_time = current_time() - philo->data->start_time;
}

void	eat(t_philo *philo)
{
	printf("%lld %d is eating\n", current_time() - philo->data->start_time, philo->id);
	ft_sleep(philo->data->time_to_eat);
	philo->has_ate_n_times++;
}

void	drop_n_sleep(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->forks[philo->id-1]);
	pthread_mutex_unlock(&philo->data->forks[philo->id % philo->data->nbr_philos]);
	if (philo->data->max_eating_cycles > -1
		&& philo->has_ate_n_times >= philo->data->max_eating_cycles)
		philo->ate_enough = TRUE;
	if (philo->ate_enough == FALSE)
	{
		printf("%lld %d is sleeping\n", current_time() - philo->data->start_time, philo->id);
		ft_sleep(philo->data->time_to_sleep);
		printf("%lld %d is thinking\n", current_time() - philo->data->start_time, philo->id);
	}
}

//!TODO fix error for one philo
void	*routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->ready_set);
	pthread_mutex_unlock(&philo->data->ready_set);
	//!look into waiting function rather than usleep -- as problem arises for large numbers
	if (philo->id % 2 == 0)
		ft_sleep(50);
	while (1)
	{
		philo->start_time = current_time() - philo->data->start_time;
		if (philo->data->max_eating_cycles == 0)
			break ;
		takeforks(philo);
		eat(philo);
		drop_n_sleep(philo);
		if (philo->ate_enough == TRUE)
		{
			philo->data->exit_flag++;
			break ;
		}
	}
	return (NULL);
}
