/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:57:55 by glacroix          #+#    #+#             */
/*   Updated: 2023/08/17 14:51:38 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

int	is_number(char *str)
{
	int	i;
	
	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i++]))
			return (0);
	}
	return(1);
}

size_t	get_time(void)
{
	struct timeval	time;
	size_t			current_time;

	gettimeofday(&time, NULL);
	current_time = (time.tv_sec) * 1000 + (time.tv_usec) / 1000;	
	return (current_time);	
}
