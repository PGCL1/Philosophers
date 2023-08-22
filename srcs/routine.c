/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 18:13:29 by glacroix          #+#    #+#             */
/*   Updated: 2023/08/22 15:55:09 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

//timestamp_in_ms X has taken a fork


static void takeforks(t_philo *philo)
{
	if (philo->fork_counter == 2)
		return ;
	pthread_mutex_lock(&philo->data->forks[LEFT]);
	printf(ORANGE"%ld %d has taken a left fork with adi %p\n"RESET, TIME_SPENT, philo->id, &philo->data->forks[LEFT]);
	philo->fork_counter++;
	pthread_mutex_lock(&philo->data->forks[RIGHT]);
	printf(ORANGE"%ld %d has taken a right fork with adi %p\n"RESET, TIME_SPENT, philo->id, &philo->data->forks[RIGHT]);
	philo->fork_counter++;
	
}

static void eat(t_philo *philo)
{
	if (philo->fork_counter == 2)
	{
		printf("ID: %d\n", philo->id);
		usleep(TIME_TO_EAT);
		printf(GREEN"%ld %d is eating\n"RESET, TIME_SPENT, philo->id);
		philo->has_ate = 1;
	}
}

static void putforks(t_philo *philo)
{
	if (philo->has_ate)
	{
		pthread_mutex_unlock(&philo->data->forks[LEFT]);
		printf(RED"%ld %d is putting down the left fork\n"RESET, TIME_SPENT, philo->id);
		pthread_mutex_unlock(&philo->data->forks[RIGHT]);
		printf(RED"%ld %d is putting down the right fork\n"RESET, TIME_SPENT, philo->id);
	}
	philo->fork_counter = 0;
}

void *routine(t_philo *philo)
{
	//pthread_mutex_lock(philo->data->buffer);
	printf("id is: %d\n", philo->id);
	if (philo->id % 2 == 0)
		usleep(800);
	while (1)
	{
		takeforks(philo);
		eat(philo);
		putforks(philo);
	}
	//pthread_mutex_unlock(philo->data->buffer);
	return (NULL);
}

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