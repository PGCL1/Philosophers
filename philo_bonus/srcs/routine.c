/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 14:31:27 by glacroix          #+#    #+#             */
/*   Updated: 2023/09/08 16:54:33 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static void	logs(t_philo *philo, const char *str)
{
	//pthread_mutex_lock(&philo->data->log_mutex);
	if (philo->data->log == FALSE)
	{
	//	pthread_mutex_unlock(&philo->data->log_mutex);
		return ;
	}
	else
		printf("%lld %d %s\n", current_time()
			- philo->data->start_time, philo->id, str);
	//pthread_mutex_unlock(&philo->data->log_mutex);
}

void	takeforks(t_philo *philo)
{
	//pthread_mutex_lock(&philo->data->forks[philo->id - 1]);
	sem_wait(philo->data->forks);
	logs(philo, "has taken a fork");
	if (philo->data->n_philos == 1)
		return ;
	//pthread_mutex_lock(&philo->data->forks[philo->id % philo->data->nbr_philos]);
	sem_wait(philo->data->forks);
	logs(philo, "has taken a fork");
	//pthread_mutex_lock(&philo->data->finished_eating_mutex);
	philo->finished_eating_time = current_time() - philo->data->start_time;
	//pthread_mutex_unlock(&philo->data->finished_eating_mutex);
}

void	eat(t_philo *philo)
{
	if (philo->data->n_philos == 1)
		return ;
	logs(philo, "is eating");
	ft_sleep(philo->data->time_to_eat);
	philo->ate_count++;
}

void	drop_n_sleep(t_philo *philo)
{
	//pthread_mutex_unlock(&philo->data->forks[philo->id - 1]);
	//pthread_mutex_unlock(&philo->data->forks[philo->id % philo->data->nbr_philos]);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
	if (philo->data->n_philos == 1)
		return ;
	if (philo->data->max_eating_cycles > -1
		&& philo->ate_count >= philo->data->max_eating_cycles)
		philo->ate_enough = TRUE;
	if (philo->ate_enough == FALSE)
	{
		logs(philo, "is sleeping");
		ft_sleep(philo->data->time_to_sleep);
		logs(philo, "is thinking");
	}
}

void	routine(t_philo *philo)
{
	int	stop;

	stop = 0;
	//pthread_mutex_lock(&philo->data->ready_set);
	//pthread_mutex_unlock(&philo->data->ready_set);
	while (!stop)
	{
		philo->start_time = current_time() - philo->data->start_time;
		if (philo->data->max_eating_cycles == 0)
			stop = 1;
		takeforks(philo);
		eat(philo);
		drop_n_sleep(philo);
		routine_stop(philo, &stop);
	}
	return ;
}
