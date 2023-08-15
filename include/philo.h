/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:38:57 by glacroix          #+#    #+#             */
/*   Updated: 2023/08/15 17:28:07 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>

typedef struct t_data {
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				test;
	int				max_eating_cycles;
	int				nbr_philos;
	pthread_mutex_t forks;
} t_data;

typedef struct t_philo {
	int 		id;
	pthread_t	thread;
	int 		has_left_fork;
	int 		has_right_fork;
	int 		philo_quantity;
	size_t		time_to_die;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	int			max_cycles;
	t_data		*data;
} t_philo;

# define TRUE 1
# define FALSE 0

int		args_wrong(int argc, char** argv);
int		ft_isdigit(char c);
int		is_number(char *str);
void	args_init(int argc, char** argv, t_data *data);
int		philos_init(t_data *data);
void	*routine(t_philo *philo);


#endif