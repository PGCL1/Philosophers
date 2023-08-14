/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:44:27 by glacroix          #+#    #+#             */
/*   Updated: 2023/08/14 20:17:32 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	philo_init(int argc, char** argv)
{
	(void)argc;
	//getting the number of philos
	int number_of_philos = atoi(argv[1]);
	printf("There are %d philos\n", number_of_philos);

	//getting the time_to_die arg
	struct timeval test;
	gettimeofday(&test, NULL);
	size_t time_in_mill = (test.tv_sec) * 1000 + (test.tv_usec) / 1000 ; 
	printf("time is %ld\n",time_in_mill);
}
