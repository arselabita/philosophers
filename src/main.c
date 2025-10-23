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

static void *start_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->mutex.printing);
	printf("Philosofer %d\n", philo->index);
	pthread_mutex_unlock(&philo->mutex.printing);
	return (NULL);
}
static int philos_init_and_run(int argc, char **argv, t_philo **philos)
{
	int conv_philos_num;
	int i;
	(void)argc;
	t_philo *philo = *philos;

	conv_philos_num = atoi(argv[1]);
	if (conv_philos_num <= 0)
		return(perror("Invalid number of philosophers.\n"), INVALID_PHILOS);
	philo = calloc(conv_philos_num, sizeof(t_philo));
	if (!philo)
		return (*philos = NULL, ALLOCATING_FAILED);
	i = 0;
	pthread_mutex_init(&philo->mutex.printing, NULL);
	while(i < conv_philos_num)
	{
		philo[i].index = i + 1;
		if(pthread_create(&philo[i].thread, NULL, &start_routine, &philo[i]) != 0)
			return (perror("Failed to create thread.\n"), FAILED_CREATING_THREADS);
		i++;
	}
	usleep(100);
	i = 0;
	while (i < conv_philos_num)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
			return (perror("Failed to join threads.\n"), FAILED_JOINING_THREADS);
		printf("Thread %d has finished execution.\n", philo[i].index);
		i++;
	}
	return (0);
}
int main(int argc, char **argv)
{
	t_philo *philos;
	int result;

	if (argc != 2)
		return (EXIT_FAILURE);
	result = philos_init_and_run(argc, argv, &philos);
	if (result != 0)
		return (perror("The philos crashed boo.\n"), ERR_PHILOS_FUNCT);
	pthread_mutex_destroy(&philos->mutex.printing);
	free(philos);
	return (0);
}
