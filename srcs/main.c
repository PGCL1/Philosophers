/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:41:20 by glacroix          #+#    #+#             */
/*   Updated: 2023/08/17 15:50:52 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

//./philo nbr_philo time_to_die time_to_eat time_to_sleep [options]

/*
Routine:
1. pick up the two forks // forks should be mutexes
	pick_up(fork[i]);
	pick_up(fork[i+1] % nbr_philos); //so when we get to the last philo he picks up the first fork 6 % 5 == 1
2. eat
3. put down the two forks
4. sleep
*/

int	main(int argc, char **argv)
{
	t_data	data;

	if (args_wrong(argc, argv) == TRUE)
		return (printf("Params are wrong\n"), 1);
	args_init(argc, argv, &data);
	threads_init(&data);
	return (0);
}
