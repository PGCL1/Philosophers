/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 19:32:04 by glacroix          #+#    #+#             */
/*   Updated: 2023/08/14 20:17:28 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	args_wrong(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc < 4 || argc > 5)
		return (1);
	//parsing text first
	while (argv[++i] != '\0')
		if (is_number(argv[i]) == FALSE)
			return (1);
	return (0);
}
