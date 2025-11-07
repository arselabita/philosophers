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

static void *start_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;

	// syncronize... if any pthreadcreate failed return NULL

	// print_msg(philo, "is thinking");
	// usleep(500 * 1000);
	
	// calling a function for even philos
	philo->not_dead = 0
	while (!philo->not_dead)
	{
		philo_monitoring(philo);
	}
		

	// printf("%d Philosofer %d is thinking.\n",millisec, philo->philo_id);
	// printf("%d Philosofer %d has taken a fork.\n", millisec, philo->philo_id);
	// printf("%d Philosofer %d is eating.\n", millisec, philo->philo_id);
	// printf("%d Philosofer %d has finished.\n", millisec, philo->philo_id);
	
	return (NULL);
}

int init_run_thread(t_data *data, t_philo **philo)
{
	int i;

	*philo = ft_calloc(data->num_of_philos, sizeof(t_philo));
	if (!*philo)
		return (ERR_ALLOCATING);
	i = 0;
	while (i < data->num_of_philos)
	{
		(*philo)[i].philo_id = i + 1;
		(*philo)[i].data = data;
		if(pthread_create(&(*philo)[i].philo_thread, NULL, &start_routine, &(*philo)[i]) != 0)
			return (print_error("Failed to create thread.\n"), ERR_CREATING_THREADS);
		usleep(100);
		i++;
	}
	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_join((*philo)[i].philo_thread, NULL) != 0) // waits for all threads to finish
			return (print_error("Failed to join threads.\n"), ERR_JOINING_THREADS);
		printf("Thread %d has finished execution.\n", (*philo)[i].philo_id);
		i++;
	}
	i = 0;
	while (i < data->num_of_philos)
		pthread_mutex_destroy(&data->fork[i++]);
	pthread_mutex_destroy(&data->printing);
	free(*philo);
	return (EXIT_SUCCESS);
}

