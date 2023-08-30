/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   schedule.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 18:13:29 by glacroix          #+#    #+#             */
/*   Updated: 2023/08/30 15:47:49 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	philo_died(t_philo *philo)
{
	//!here is the problem -- hello data race :))))
	if (philo->data->philo_died == TRUE)
		return (1);
	else if (current_time() - philo->data->start_time - philo->finished_eating_time >= philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->data->death_mutex);
		philo->data->philo_died = TRUE;
		philo->dead = TRUE;
		pthread_mutex_unlock(&philo->data->death_mutex);
		return (1);
	}
	return (0);
}

void	takeforks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->id-1]);
	if (philo_died(philo) == 1)
		return ;
	printf("%lld %d has taken a fork\n", current_time() - philo->data->start_time, philo->id);
	if (philo->data->nbr_philos == 1)
		return;
	pthread_mutex_lock(&philo->data->forks[philo->id % philo->data->nbr_philos]);
	printf("%lld %d has taken a fork \n", current_time() - philo->data->start_time, philo->id);
	philo->finished_eating_time = current_time() - philo->data->start_time;
}

void	eat(t_philo *philo)
{
	if (philo_died(philo) == 1)
		return ;
	if (philo->data->nbr_philos == 1)
		return ;
	printf("%lld %d is eating\n", current_time() - philo->data->start_time, philo->id);
	ft_sleep(philo->data->time_to_eat);
	philo->ate_count++;
}

void	drop_n_sleep(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->forks[philo->id-1]);
	pthread_mutex_unlock(&philo->data->forks[philo->id % philo->data->nbr_philos]);
	if (philo_died(philo) == 1)
		return ;
	if (philo->data->nbr_philos == 1)
		return ;
	if (philo->data->max_eating_cycles > -1
		&& philo->ate_count >= philo->data->max_eating_cycles)
		philo->ate_enough = TRUE;
	if (philo->ate_enough == FALSE && philo->data->philo_died == FALSE)
	{
		printf("%lld %d is sleeping\n", current_time() - philo->data->start_time, philo->id);
		ft_sleep(philo->data->time_to_sleep);
		printf("%lld %d is thinking\n", current_time() - philo->data->start_time, philo->id);
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
		if (philo->data->philo_died == TRUE || philo->data->nbr_philos == 1)
			break ;
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
