/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:56:38 by glacroix          #+#    #+#             */
/*   Updated: 2023/09/08 16:54:21 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	routine_stop(t_philo *philo, int *stop)
{
	//pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->philo_died == TRUE)
	{
	//	pthread_mutex_unlock(&philo->data->death_mutex);
		*stop = 1;
	}
	//pthread_mutex_unlock(&philo->data->death_mutex);
	if (philo->data->n_philos == 1)
		*stop = 1;
	if (philo->ate_enough == TRUE)
	{
	//	pthread_mutex_lock(&philo->data->max_eat_mutex);
		philo->data->exit_flag++;
	//	pthread_mutex_unlock(&philo->data->max_eat_mutex);
		*stop = 1;
	}
}
