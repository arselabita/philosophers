/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abita <abita@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 11:07:50 by abita             #+#    #+#             */
/*   Updated: 2025/10/24 19:45:17 by abita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// playing around with threads
// how to create a thread? -> we are going to use 

int getmillisec()
{
	struct timeval tv;
	if (gettimeofday(&tv, NULL) == -1)
		return (perror("Failed to give time of day.\n"), ERRNO_GET_TIME);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	// Convering to seconds to milliseconds and microseconds too
}

static void *start_routine(void *arg)
{
	t_philo *philo;
	int millisec;

	millisec = getmillisec();
	printf("%d ", millisec);
	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->printing);
	printf("Philosofer %d\n", philo->index);
	pthread_mutex_unlock(&philo->printing);
	return (NULL);
}

int main(int argc, char **argv)
{
	t_philo *philos;
	int convert_to_number;
	int i;

	if (argc != 2)
		return (EXIT_FAILURE);
	if ((convert_to_number = ft_atoi(argv[1])) <= 0)
		return(perror("Invalid number of philosophers.\n"), INVALID_PHILOS);
	philos = ft_calloc(convert_to_number, sizeof(t_philo));
	if (!philos)
		return (ALLOCATING_FAILED);
	i = 0;
	pthread_mutex_init(&philos->printing, NULL);
	while (i < convert_to_number)
	{
		philos[i].index = i + 1;
		if(pthread_create(&philos[i].thread, NULL, &start_routine, &philos[i]) != 0)
			return (perror("Failed to create thread.\n"), FAILED_CREATING_THREADS);
		i++;
	}
	usleep(100);
	i = 0;
	while (i < convert_to_number)
	{
		if (pthread_join(philos[i].thread, NULL) != 0)
			return (perror("Failed to join threads.\n"), FAILED_JOINING_THREADS);
		printf("Thread %d has finished execution.\n", philos[i].index);
		i++;
	}
	pthread_mutex_destroy(&philos->printing);
	free(philos);
	return (0);
}
