/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:38:57 by glacroix          #+#    #+#             */
/*   Updated: 2023/08/22 15:54:33 by glacroix         ###   ########.fr       */
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

# define RESET  		"\x1B[0m"
# define RED  			"\x1B[31m"
# define GREEN	  		"\x1B[32m"
# define YELLOW  		"\x1B[33m"
# define BLUE 			"\x1B[34m"
# define MAGENTA 		"\x1B[35m"
# define CAYN  			"\x1B[36m"
# define WHITE  		"\x1B[37m"
# define ORANGE			"\x1b[38;5;209m"

typedef struct t_data {
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				test;
	int				max_eating_cycles;
	int				nbr_philos;
	pthread_mutex_t *forks;
	pthread_mutex_t *buffer;
} t_data;

typedef struct t_philo {
	int 		id;
	pthread_t	thread;
	int			state;
	size_t		start_time;
	size_t		last_meal;
	int			fork_counter;
	int			has_ate;
	t_data		*data;
} t_philo;


# define TRUE 1
# define FALSE 0


# define LEFT (philo->id - 1)
# define RIGHT (philo->id % philo->data->nbr_philos)
# define TIME_SPENT (get_time() - philo->data->start_time)
# define TIME_TO_EAT (philo->data->time_to_eat * 1000)
# define TIME_TO_DIE (philo->data->time_to_die * 1000)

int		args_wrong(int argc, char** argv);
int		ft_isdigit(char c);
int		is_number(char *str);
void	args_init(int argc, char** argv, t_data *data);
int		threads_init(t_data *data);
void	*routine(t_philo *philo);
size_t	get_time(void);


#endif