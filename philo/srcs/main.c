/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:41:20 by glacroix          #+#    #+#             */
/*   Updated: 2023/08/24 15:23:04 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
//./philo nbr_philo time_to_die philo->data->time_to_eat*1000 time_to_sleep [options]
int	main(int argc, char **argv)
{
	t_data	data;

	if (args_wrong(argc, argv) == TRUE)
		return (printf("Params are wrong\n"), 1);
	args_init(argc, argv, &data);
	threads_init(&data);
	return (0);
}
