/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:30:55 by glacroix          #+#    #+#             */
/*   Updated: 2023/09/15 20:06:14 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static int init_semaphore(t_data *data)
{
	sem_unlink("/forks");
	sem_unlink("/death");
	data->sem_death = sem_open("/death", O_CREAT, 0644, 1);
	data->forks = sem_open("/forks", O_CREAT, 0644, data->n_philos);
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
	int		j = -1;
	int		exit_flag = 0;

	philo = malloc(sizeof(philo) * data->n_philos);
	if (!philo)
		return (ft_putstr_fd("Error when mallocing philo\n", 2), 1);
	for (int i = 0; i < data->n_philos; i++)
	{
		philo[i].pidC = fork();
		philo[i].id = i + 1;
		philo[i].log = TRUE;
		philo[i].ate_count = 0;
		philo[i].data = data;
		data->start_time = current_time();
		if (philo[i].pidC < 0)
			return (ft_putstr_fd("Error when creating process\n", 2), 1);
		if (philo[i].pidC == 0)
			routine(philo + i);
	}
	
	waitpid(-1, &status, 0);
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == EXIT_DEATH)
		{
			printf("here\n");
			while (++j < data->n_philos)
				kill(philo[j].pidC, SIGKILL);
			return 0;
		}
		if (WEXITSTATUS(status) == EXIT_EAT)
		{
			exit_flag += 1;
			if (exit_flag == data->n_philos)
				return 1;
		}
	}
	if (sem_close(data->forks) == -1)
		return (ft_putstr_fd("Error when closing the semaphore\n", 2), 1);
	if (sem_unlink("/forks") == -1)
		return (ft_putstr_fd("Error when unlinking the semaphore\n", 2), 1);
	if (sem_unlink("/death") == -1)
		return (ft_putstr_fd("Error when unlinking the semaphore\n", 2), 1);
	return (0);
}

/*
1 800 200 200				problem -- death is not printed
a philo should die
4 310 200 100				problem -- death is not printed
a philo should die
4 200 205 200				problem	seems like deadlock..-but weird
a philo should die
5 800 200 200 7				problem with printing after the program ends
no one should die, simulation should stop after 7 eats
4 410 200 200 10
no one should die, simulation should stop after 10 eats
-5 600 200 200
should error and not run (no crashing)
4 -5 200 200
should error and not run (no crashing)
4 600 -5 200
should error and not run (no crashing)
4 600 200 -5
should error and not run (no crashing)
4 600 200 200 -5
should error and not run (no crashing)
//--------------------------------------------
5 800 200 200
no one should die
5 600 150 150
no one should die
4 410 200 200
no one should die
100 800 200 200
no one should die
105 800 200 200				small problem with printing -- everything is not on one line
no one should die
200 800 200 200				happens something problem with printing
no one should die
*/
