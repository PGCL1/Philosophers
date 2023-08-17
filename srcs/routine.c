/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 18:13:29 by glacroix          #+#    #+#             */
/*   Updated: 2023/08/17 19:02:51 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

//timestamp_in_ms X has taken a fork

static void pick_up_left_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->data->forks);
	printf(GREEN"%ld %d has taken a left fork\n"RESET, get_time(), philo->id);
	pthread_mutex_unlock(philo->data->forks);
}

static void pick_up_right_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->data->forks);
	printf(GREEN"%ld %d has taken a right fork\n"RESET, get_time(), philo->id);
	pthread_mutex_unlock(philo->data->forks);
}

void *ft_eat(t_philo *philo)
{
	pick_up_left_fork(philo);
	pick_up_right_fork(philo);
	printf("Bf eating: %ld\n", get_time());
	usleep(philo->data->time_to_eat);
	printf("Af eating: %ld\n", get_time());
	return NULL;
}

void *ft_sleep(t_philo *philo)
{
	(void)philo;
	usleep(200);
	printf("I'm waiting\n");
	return NULL;
}

void *routine(t_philo *philo)
{
	while (1)
	{
		//wait
		//eat
		//sleep
	}
	return (NULL);
};

//need to calculate a start time for the simulation
//to eat, each philo must have two forks
//per philo, need to have a start time or start = end of their last meal
//once they start eating (eating_time = get_time() + eat_time) then they drop their two forks
//once a philo finishes eating, he goes to sleep
//then philo[n+1] back to the top

/*
to start eating, the philosopher need his lowered number fork as in
ROUND 1:
philo 1 has fork 1 -> pick fork 1 and pick fork 2 -> eat
philo 2 has fork 2 -> wait because doesnt have fork 2 -> wait
philo 3 has fork 3 -> pick fork 3 and pick fork 4 -> eat
philo 4 has fork 4 -> wait because doesnt have fork 4 -> wait

ROUND 2:
philo 1 has fork 1 -> puts down fork 1 and fork 2 -> sleep
philo 3 has fork 3 -> puts down fork 3 and fork 4 -> sleep
philo 2 has fork 2 -> picks up fork 2 and fork 3 -> eat
philo 4 has fork 4 -> picks up fork 4 and fork 1 -> eat

ROUND 3:
philo 4 has fork 4 -> puts down fork 3 and fork 4 -> sleep
philo 1 has fork 1 -> puts down fork 1 and fork 2 -> sleep
philo 2 has fork 2 -> picks up fork 2 and fork 3 -> eat
philo 3 has fork 3 -> picks up fork 3 and fork 4 -> eat

to eat the philosopher take the higher numbered fork next to him and then the lowered numbered fork

*/