/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glacroix <glacroix@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:44:09 by glacroix          #+#    #+#             */
/*   Updated: 2023/08/11 11:54:47 by glacroix         ###   ########.fr       */
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
 	int value = (rand() % 6) + 1;
	int* res = malloc(sizeof(int));
	
	*res = value;
	return (void*)res;
};

int main()
{
	pthread_t philo[50];
	int i;
	int* res;
	//creating a random variable
	srand(time(NULL));
	//first, we create the threads
	for (int i = 0; i < 50; i++){
		if (pthread_create(philo + i, NULL, &routine, NULL))
		{
			perror("There was an error when creating the thread\n");
			return 1;
		}
	}
	//then we wait for the execution of the threads to end
	for (int i = 0; i < 50; i++){
		if (pthread_join(philo[i], (void**) &res))
		{
			perror("There was an error when finishing the execution of the thread\n");
			return 2;
		}
		printf("For Philo[%d]: res's address is %p\n", i, &res);
		printf("For Philo[%d]: res is %d\n", i, *res);
	}
	return (0);
	
}