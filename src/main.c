/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abita <abita@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 11:07:50 by abita             #+#    #+#             */
/*   Updated: 2025/09/29 11:07:51 by abita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// playing around with threads
// how to create a thread? -> we are going to use 

void *routine(void *arg)
{
	int philo_index;

	philo_index = *(int *)arg;
	printf("Philosofer %d\n", philo_index);
	free(arg);
	return (NULL);
}

int main(int argc, char **argv)
{
	t_philo *philos;
	int conv_philos_num;
	int i;

	if (argc != 2)
		return (EXIT_FAILURE);
	conv_philos_num = atoi(argv[1]);
	if (conv_philos_num <= 0)
		return(perror("Invalid number of philosophers.\n"), INVALID_PHILOS);
	philos = calloc(conv_philos_num, sizeof(pthread_t));
	if (!philos)
		return (ALLOCATING_FAILED);
	i = 0;
	while(i < conv_philos_num)
	{
		philos[i].index = i + 1;
		if(pthread_create(&philos[i].thread, NULL, &routine, &philos[i]) != 0)
			return (perror("Failed to create thread.\n"), FAILED_CREATING_THREADS);
		i++;
	}
	i = 0;
	while (i < conv_philos_num)
	{
		if (pthread_join(philos[i].thread, NULL) != 0)
			return (perror("Failed to join threads.\n"), FAILED_JOINING_THREADS);
		printf("Thread %d has finished execution.\n", philos[i].index);
	}
	free(philos);
	return (0);
}
