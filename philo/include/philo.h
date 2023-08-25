/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:38:57 by glacroix          #+#    #+#             */
/*   Updated: 2023/08/25 21:22:47 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <unistd.h>

/*Print Colors----------------------------------------------------------------*/
# define RESET  		"\x1B[0m"
# define RED  			"\x1B[31m"
# define GREEN	  		"\x1B[32m"
# define YELLOW  		"\x1B[33m"
# define BLUE 			"\x1B[34m"
# define MAGENTA 		"\x1B[35m"
# define CYAN  			"\x1B[36m"
# define WHITE  		"\x1B[37m"
# define ORANGE			"\x1b[38;5;209m"

/*Data Structures-------------------------------------------------------------*/
typedef struct	t_data {
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				max_eating_cycles;
	int				nbr_philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	ready_set;
	pthread_mutex_t	death_mutex;
}				t_data;

typedef struct	t_philo {
	pthread_t	thread;
	size_t		start_time;
	size_t		finished_eating_time;
	int			id;
	int			dead;
	int			has_left_fork;
	int			has_right_fork;
	int			flag_max_meals;
	int			has_ate_n_times;
	t_data		*data;
}				t_philo;

/*Homemade boolean------------------------------------------------------------*/
# define TRUE 1
# define FALSE 0

/*Shortcuts-------------------------------------------------------------------*/


/*1) Init---------------------------------------------------------------------*/
void	args_init(int argc, char **argv, t_data *data);
int		threads_init(t_data *data);

/*2) Utils--------------------------------------------------------------------*/
int		args_wrong(int argc, char **argv);
int		ft_isdigit(char c);
int		is_number(char *str);
size_t	current_time(void);
int		ft_atoi(char *str);
void	ft_sleep(size_t time);

/*3) Routine------------------------------------------------------------------*/
void	*routine(t_philo *philo);
void	takeforks(t_philo *philo);
void	eat(t_philo *philo);
void	drop_n_sleep(t_philo *philo);
void	philo_died(t_philo *philo);

#endif