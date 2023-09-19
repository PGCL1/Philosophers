/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 14:31:27 by glacroix          #+#    #+#             */
/*   Updated: 2023/09/19 16:04:41 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static void	logs(t_philo *philo, const char *str)
{
	/*if (philo->log == FALSE)
		return ;
	else*/
	sem_wait(philo->data->sem_print);
	printf("%lld %d %s\n", current_time()
			- philo->data->start_time, philo->id, str);
	sem_post(philo->data->sem_print);
}

void	takeforks(t_philo *philo)
{
	sem_wait(philo->data->forks);
	logs(philo, "has taken a fork");
	if (philo->data->n_philos == 1)
		ft_sleep(philo->data->time_to_die, philo);
	sem_wait(philo->data->forks);
	logs(philo, "has taken a fork");
	philo->finished_eating_time = current_time() - philo->data->start_time;
}

void	eat(t_philo *philo)
{
	logs(philo, "is eating");
	ft_sleep(philo->data->time_to_eat, philo);
	philo->ate_count++;
}

void	drop_n_sleep(t_philo *philo)
{
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
	if (philo->data->max_eating_cycles > -1
		&& philo->ate_count >= philo->data->max_eating_cycles)
		exit(EXIT_EAT);
	logs(philo, "is sleeping");
	ft_sleep(philo->data->time_to_sleep, philo);
	logs(philo, "is thinking");
}

void	routine(t_philo *philo)
{
	while (1)
	{
		sem_wait(philo->data->sem_start_time);
		philo->start_time = current_time() - philo->data->start_time;
		sem_post(philo->data->sem_start_time);
		if (philo->data->max_eating_cycles == 0)
			exit(EXIT_EAT);
		takeforks(philo);
		eat(philo);
		drop_n_sleep(philo);
	}
	return ;
}
