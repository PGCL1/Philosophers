/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 11:45:31 by glacroix          #+#    #+#             */
/*   Updated: 2023/09/04 15:04:10 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

size_t	ft_strlen(const char *str)
{
	size_t	x;

	x = 0;
	while (str[x] != '\0')
		x++;
	return (x);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	if (s && fd >= 0)
	//writing everything with strlen
		write(fd, s, ft_strlen(s));
}

void	mutexes_destroy(t_data *data)
{
	pthread_mutex_destroy(data->forks);
	pthread_mutex_destroy(&data->ready_set);
	pthread_mutex_destroy(&data->log_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	pthread_mutex_destroy(&data->finished_eating_mutex);
	pthread_mutex_destroy(&data->max_eat_mutex);
}
