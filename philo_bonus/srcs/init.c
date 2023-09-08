/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:30:55 by glacroix          #+#    #+#             */
/*   Updated: 2023/09/08 16:54:41 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static int init_semaphore(t_data *data)
{
	int	i;

	i = -1;
	data->sem_name = "/philo";
	sem_unlink(data->sem_name);
	data->forks = sem_open(data->sem_name, O_CREAT, 0644, data->n_philos);
	if (data->forks == SEM_FAILED)
		return(ft_putstr_fd("Error when creating the semaphore\n", 2), 1);
	return (0);
}

int	init_args(int argc, char **argv, t_data *data)
{
	data->n_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (data_wrong(data) == TRUE)
		return (1);
	data->philo_died = FALSE;
	data->log = TRUE;
	data->exit_flag = 0;
	if (argc == 6)
		data->max_eating_cycles = ft_atoi(argv[5]);
	else
		data->max_eating_cycles = -1;
 	if (init_semaphore(data) == 1)
		return (1);
	return (0);
}

int	init_processes(t_data *data)
{
	t_philo	*philo;
	int		status = 0;

	philo = malloc(sizeof(philo) * data->n_philos);
	if (!philo)
		return (ft_putstr_fd("Error when mallocing philo\n", 2), 1);
	for (int i = 0; i < data->n_philos; i++)
	{
		philo[i].pidC = fork();
		philo[i].id = i + 1;
		philo[i].ate_enough = FALSE;
		philo[i].exit_flag = FALSE;
		philo[i].ate_count = 0;
		philo[i].data = data;
		data->start_time = current_time();
		if (philo[i].pidC < 0)
			return (ft_putstr_fd("Error when creating process\n", 2), 1);
		data->start_time = current_time();
		if (philo[i].pidC == 0)
		{
			routine(&philo[i]);
			exit(0); // or status
		}
		else
			continue;
	}
	//sleep(2);
	for (int i = 0; i < data->n_philos; i++)
	{
		philo[i].pidC = wait(&status);
		//printf("Padre PID = %d | Child PID = %d stopped | status child %d\n", getpid(), philo[i].pidC, status);
	}
	if (sem_close(data->forks) == -1)
		return (ft_putstr_fd("Error when closing the semaphore\n", 2), 1);
	if (sem_unlink(data->sem_name) == -1)
		return (ft_putstr_fd("Error when unlinking the semaphore\n", 2), 1);
	return (0);
}
