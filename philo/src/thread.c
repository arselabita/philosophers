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

static void	*philo_thread_start(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	/////////
	// syncronize... if any pthread_create failed return NULL
	////////
	run_philo_thread(philo); // here i do sleeping, eating, thinking
	return (NULL);
}
static void	*start_monitoring(void *arg)
{
	////////////////////////////
	// All philosophers store the address of data->dead_flag.
	// So when any thread updates it, everyone else sees the change
	// immediately (shared memory).
	///////////////////////////
	t_philo	*philo;

	philo = (t_philo *)arg;

	while (philo->data->dead_flag == 0)
	{
		int i = 0;
		
		while (i < philo->data->num_of_philos)
		{
			if (getmillisec() - philo[i].last_meal > philo->data->time.time_to_die)
			{
				pthread_mutex_lock(&philo->data->dead_mutex);
				if (philo->data->dead_flag == 0)
					print_msg(&philo[i], "died");
				*philo->dead = 1;
				pthread_mutex_unlock(&philo->data->dead_mutex);
				return (NULL);
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

int	init_run_thread(t_data *data, t_philo **philo)
{
	int	i;

	*philo = ft_calloc(data->num_of_philos, sizeof(t_philo));
	if (!*philo)
		return (ERR_ALLOCATING);
	i = 0;
	while (i < data->num_of_philos)
	{
		(*philo)[i].philo_id = i + 1;
		(*philo)[i].data = data;
		(*philo)[i].dead = &data->dead_flag; //i assign each death to the death flag
		(*philo)[i].last_meal = getmillisec();
		if (pthread_create(&(*philo)[i].philo_thread, NULL, &philo_thread_start,
				&(*philo)[i]) != 0)
			return (print_error("Failed to creating threads.\n"),
				ERR_JOINING_THREADS);
		usleep(100);
		i++;
	}
	pthread_create(&(*philo)->monitoring_thread, NULL, &start_monitoring, *philo);
	pthread_join((*philo)->monitoring_thread, NULL);
	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_join((*philo)[i].philo_thread, NULL) != 0)
			return (print_error("Failed to join threads.\n"),
				ERR_JOINING_THREADS);
		printf("Thread %d has finished execution.\n", (*philo)[i].philo_id);
		i++;
	}
	i = 0;
	while (i < data->num_of_philos)
		pthread_mutex_destroy(&data->fork[i++]);
	free((*philo)->data->fork);
	pthread_mutex_destroy(&data->printing);
	free(*philo);
	return (EXIT_SUCCESS);
}
