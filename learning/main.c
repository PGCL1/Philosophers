/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:44:09 by glacroix          #+#    #+#             */
/*   Updated: 2023/08/23 13:12:00 by glacroix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

int mails = 0;
pthread_mutex_t mutex;

//we need to create the routine
void* routine(){
 	for (int i = 0; i < 10000; i++)
		mails++;
	return (NULL);
}

int main()
{
	pthread_t philo[4];
	//first, we create the threads
	for (int i = 0; i < 4; i++)
	{
		if (pthread_create(philo + i, NULL, &routine, NULL))
			return (perror("There was an error when creating the thread\n"), 1);
	}
	//then we wait for the execution of the threads to end
	for (int i = 0; i < 4; i++)
	{
		if (pthread_join(philo[i], NULL))
			return (printf("error execution\n"), 2);
	}
	return (0);
	
}