/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   schedule.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 18:13:29 by glacroix          #+#    #+#             */
/*   Updated: 2023/09/01 19:55:21 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	philo_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->finished_eating_mutex);
	if (philo->data->philo_died == TRUE)
	{
		pthread_mutex_unlock(&philo->data->finished_eating_mutex);
		return (1);
	}
	else if (current_time() - philo->data->start_time - philo->finished_eating_time >= philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->data->death_mutex);
		philo->data->philo_died = TRUE;
		pthread_mutex_unlock(&philo->data->death_mutex);
		pthread_mutex_lock(&philo->data->log_mutex);
		philo->data->log = FALSE;
		pthread_mutex_unlock(&philo->data->log_mutex);
		pthread_mutex_unlock(&philo->data->finished_eating_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->finished_eating_mutex);
	return (0);
}


static void	logs(t_philo *philo, const char *str)
{
	pthread_mutex_lock(&philo->data->log_mutex);
	if (philo->data->log == FALSE)
	{
		pthread_mutex_unlock(&philo->data->log_mutex);
		return ;
	}
	else
		printf("%lld %d %s\n", current_time() - philo->data->start_time, philo->id, str);
	pthread_mutex_unlock(&philo->data->log_mutex);
}

void	takeforks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->id-1]);
	logs(philo, "has taken a fork");
	if (philo->data->nbr_philos == 1)
		return;
	pthread_mutex_lock(&philo->data->forks[philo->id % philo->data->nbr_philos]);
	logs(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->finished_eating_mutex);
	philo->finished_eating_time = current_time() - philo->data->start_time;
	pthread_mutex_unlock(&philo->data->finished_eating_mutex);
}

void	eat(t_philo *philo)
{
	if (philo->data->nbr_philos == 1)
		return ;
	logs(philo, "is eating");
	ft_sleep(philo->data->time_to_eat);
	philo->ate_count++;
}

void	drop_n_sleep(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->forks[philo->id-1]);
	pthread_mutex_unlock(&philo->data->forks[philo->id % philo->data->nbr_philos]);
	if (philo->data->nbr_philos == 1)
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

//* DONE fix error for one philo -- make it pretty now it works
//while (++i < 100000); instead of usleep umm  will see
void	*schedule(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->ready_set);
	pthread_mutex_unlock(&philo->data->ready_set);
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
		pthread_mutex_lock(&philo->data->death_mutex);
		if (philo->data->philo_died == TRUE )
		{
			pthread_mutex_unlock(&philo->data->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->death_mutex);
		if (philo->data->nbr_philos == 1)
			break;
		if (philo->ate_enough == TRUE)
		{
			pthread_mutex_lock(&philo->data->max_eat_mutex);
			philo->data->exit_flag++;
			pthread_mutex_unlock(&philo->data->max_eat_mutex);
			break ;
		}
	}
	return (NULL);
}
