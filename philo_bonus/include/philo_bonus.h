/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:38:57 by glacroix          #+#    #+#             */
/*   Updated: 2023/09/08 16:54:27 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <semaphore.h>
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
typedef struct t_data {
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		start_time;
	int				max_eating_cycles;
	int				philo_died;
	int				n_philos;
	int				log;
	int				exit_flag;
	int				val;
	sem_t			*forks;
	const char		*sem_name;
}				t_data;

typedef struct t_philo {
	pid_t		pidC;
	long long	start_time;
	long long	finished_eating_time;
	int			id;
	int			ate_count;
	int			ate_enough;
	int			exit_flag;
	t_data		*data;
}				t_philo;

/*Homemade boolean------------------------------------------------------------*/
# define TRUE 1
# define FALSE 0

/*Functions--------------------------------------------------------------------*/

//parsing
int			args_wrong(int argc, char **argv);
int			data_wrong(t_data *data);

//init
int			init_args(int argc, char **argv, t_data *data);
int 		init_processes(t_data *data);

//utils
int			ft_isdigit(char c);
void		ft_sleep(long long time);
int			is_number(char *str);
long long	current_time(void);
int			ft_atoi(char *str);
size_t		ft_strlen(const char *str);
void		ft_putstr_fd(char *s, int fd);

//routine
void		routine(t_philo *philo);
void		takeforks(t_philo *philo);
void		eat(t_philo *philo);
void		drop_n_sleep(t_philo *philo);

//routine_check
void		routine_stop(t_philo *philo, int *stop);

#endif
