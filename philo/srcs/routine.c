/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 18:13:29 by glacroix          #+#    #+#             */
/*   Updated: 2023/08/25 21:24:35 by glacroix         ###   ########.fr       */
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
	printf(WHITE"%ld %d has taken a fork\n"RESET, current_time() - philo->data->start_time, philo->id);
	pthread_mutex_lock(&philo->data->forks[philo->id % philo->data->nbr_philos]);
	printf(WHITE"%ld %d has taken a fork \n"RESET, current_time() - philo->data->start_time, philo->id);
	philo->finished_eating_time = current_time() - philo->data->start_time;
}

void	eat(t_philo *philo)
{
	printf(GREEN"%ld %d is eating\n"RESET, current_time() - philo->data->start_time, philo->id);
	ft_sleep(philo->data->time_to_eat);
	philo->has_ate_n_times++;
	if (philo->data->max_eating_cycles > -1
		&& philo->has_ate_n_times >= philo->data->max_eating_cycles)
		philo->flag_max_meals = TRUE;
}

void	drop_n_sleep(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->forks[philo->id-1]);
	pthread_mutex_unlock(&philo->data->forks[philo->id % philo->data->nbr_philos]);
	// if (philo->flag_max_meals == TRUE)
	// 	return ;
	printf(ORANGE"%ld %d is sleeping\n"RESET, current_time() - philo->data->start_time, philo->id);
	ft_sleep(philo->data->time_to_sleep);
	printf(MAGENTA"%ld %d is thinking\n"RESET, current_time() - philo->data->start_time, philo->id);
}

//!TODO fix error for one philo
void	*routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->ready_set);
	pthread_mutex_unlock(&philo->data->ready_set);
	if (philo->id % 2 == 0)
		ft_sleep(200);
	while (1)
	{
		philo->start_time = current_time() - philo->data->start_time;
		if (philo->data->max_eating_cycles == 0)
			break ;
		takeforks(philo);
		eat(philo);
		drop_n_sleep(philo);
		// if (philo->flag_max_meals == TRUE)
		// 	break ;
		//printf("ID: %d | ate %d | time since last meal: %lu\n", philo->id, philo->has_ate_n_times, philo->finished_eating_time - philo->start_time);
/* 		if (philo->finished_eating_time - philo->start_time >= philo->data->time_to_die)
		{
			printf(RED"ID: %d | %lu died//\n"RESET, philo->id, philo->finished_eating_time - philo->start_time); //philo->finished_eating_time - philo->start_time);
			philo->dead = TRUE;
		} */
		/* if (philo->id == 1)
			printf(GREEN"ID: %d => start_time: %lu | philo_starting_at: %lu\n"RESET, philo->id, philo->data->start_time, philo->start_time);
		else
			printf(CYAN"ID: %d => start_time: %lu | philo_starting_at: %lu\n"RESET, philo->id, philo->data->start_time, philo->start_time); */
	}
	return (NULL);
}



/*
philo.


*/