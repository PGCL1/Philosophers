/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:38:57 by glacroix          #+#    #+#             */
/*   Updated: 2023/08/14 20:15:15 by glacroix         ###   ########.fr       */
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

typedef struct t_philo {
	int id;
	int has_left_fork;
	int has_right_fork;
	int philo_quantity;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	max_cycles;
} t_philo;

# define TRUE 1
# define FALSE 0

int args_wrong(int argc, char** argv);
int ft_isdigit(char c);
int is_number(char *str);
void philo_init(int argc, char** argv);


#endif