/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abita <abita@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 12:35:34 by abita             #+#    #+#             */
/*   Updated: 2025/10/27 12:35:35 by abita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int getmillisec()
{
	struct timeval tv;
	if (gettimeofday(&tv, NULL) == -1)
		return (perror("Failed to give time of day.\n"), ERR_GET_TIME);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	// Convering seconds to milliseconds and microseconds too
}

static void *start_routine(void *arg)
{
	t_philo *philo;
	t_data *data;
	int millisec;

	millisec = getmillisec();
	philo = (t_philo *)arg;
	data = philo->data;
	pthread_mutex_lock(&data->printing);
	printf("%d Philosofer %d\n", millisec, philo->philo_id);
	pthread_mutex_unlock(&data->printing);

	printf("Philosopher %d is thinking.\n", philo->philo_id);
	printf("Philosopher %d has taken a fork.\n", philo->philo_id);
	printf("Philosopher %d is eating.\n", philo->philo_id);
	printf("Philosopher %d has finished.\n", philo->philo_id);
	
	return (NULL);
}

int init_run_thread(t_data *data, t_philo **philo)
{
	int i;

	*philo = ft_calloc(data->num_of_philos, sizeof(t_philo));
	if (!*philo)
		return (ERR_ALLOCATING);
	i = 0;
	pthread_mutex_init(&data->printing, NULL);
	while (i < data->num_of_philos)
	{
		(*philo)[i].philo_id = i + 1;
		(*philo)[i].data = data;
		if(pthread_create(&(*philo)[i].philo_thread, NULL, &start_routine, &(*philo)[i]) != 0)
			return (perror("Failed to create thread.\n"), ERR_CREATING_THREADS);
		usleep(100);
		i++;
	}
	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_join((*philo)[i].philo_thread, NULL) != 0) // waits for all threads to finish
			return (perror("Failed to join threads.\n"), ERR_JOINING_THREADS);
		printf("Thread %d has finished execution.\n", (*philo)[i].philo_id);
		i++;
	}
	pthread_mutex_destroy(&data->printing);
	free(*philo);
	return (EXIT_SUCCESS);
}

