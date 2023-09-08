/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:17:43 by glacroix          #+#    #+#             */
/*   Updated: 2023/09/08 12:59:16 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	ft_leaks(void)
{
	system("leaks -q philo");
}

int main(int argc, char **argv)
{
	t_data	data;

	//check args
	if (args_wrong(argc, argv) == TRUE)
		return (ft_putstr_fd("Params are wrong\n", 2), 1);
	//check params
	if (init_args(argc, argv, &data) == TRUE)
		return (ft_putstr_fd("Args are wrong\n", 2), 2);	
	//init processes
	if (init_processes(&data) == 1)
		return (ft_putstr_fd("Error when creating processes\n", 2), 3);	
	return (0);
}
