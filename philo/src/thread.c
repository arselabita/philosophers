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
	t_data	*data;
	long time_since_last_meal;
	int i;

	data = (t_data *)arg;
	i = 0;
	while (1)
	{
		pthread_mutex_lock(&data->dead_mutex);
		time_since_last_meal = getmillisec() - data->philo[i].last_meal;
		if (time_since_last_meal > data->time.time_to_die)
		{
			//puts("yolo");
			// pthread_mutex_lock(&data->printing);	
			// data->dead_flag = 1;
			// pthread_mutex_unlock(&data->printing);	
			pthread_mutex_unlock(&data->dead_mutex);
			print_msg(&data->philo[i], "died");
			break ;
		}
		pthread_mutex_unlock(&data->dead_mutex);
		if (i == data->num_of_philos)
			i = -1;
		i++;
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

	data->philo = *philo;
	i = 0;
	while (i < data->num_of_philos)
	{
		(*philo)[i].philo_id = i + 1;
		(*philo)[i].data = data;
		pthread_mutex_lock(&data->dead_mutex);
		(*philo)[i].last_meal = data->start_time;
		pthread_mutex_unlock(&data->dead_mutex);
		if (pthread_create(&(*philo)[i].philo_thread, NULL, &philo_thread_start,
				&(*philo)[i]) != 0)
			return(print_error("Failed to create philosopher thread.\n"), ERR_ALLOCATING);
		i++;
	}

	// monitoring all threads
	if (pthread_create(&(*philo)->monitoring_thread, NULL, &start_monitoring,data) != 0)
		return (print_error("Failed to create monitoring thread.\n"), ERR_ALLOCATING);
	/// joining the finished threads
	
	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_join((*philo)[i].philo_thread, NULL) != 0)
		return (print_error("Failed to join threads.\n"),
		ERR_JOINING_THREADS);
		i++;
	}

	if (pthread_join((*philo)->monitoring_thread, NULL))
		return (print_error("Failed to join monitoring thread.\n"), ERR_JOINING_THREADS);
	// freeing and destroying mutexes
	i = 0;
	while (i < data->num_of_philos)
		pthread_mutex_destroy(&data->fork[i++]);
	pthread_mutex_destroy(&data->printing);
	pthread_mutex_destroy(&data->dead_mutex);
	free(data->fork);
	free(*philo);
	return (EXIT_SUCCESS);
}
