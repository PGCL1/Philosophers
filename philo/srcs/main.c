/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:41:20 by glacroix          #+#    #+#             */
/*   Updated: 2023/09/04 14:48:52 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/* void ft_leaks()
{
	system("leaks -q philo");
} */

int	main(int argc, char **argv)
{
	t_data	data;
/* 	atexit(ft_leaks); */
	if (args_wrong(argc, argv) == TRUE)
		return (ft_putstr_fd("Params are wrong\n", 2), 1);
	init_args(argc, argv, &data);
	init_threads(&data);
	return (0);
}
