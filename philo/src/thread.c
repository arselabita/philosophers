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
// static void	*start_monitoring(void *arg)
// {
// 	t_data	*data;

// 	////////////////////////////
// 	// All philosophers store the address of data->dead_flag.
// 	// So when any thread updates it, everyone else sees the change
// 	// immediately (shared memory).
// 	///////////////////////////

// 	data = (t_data *)arg;
// 	int i = 0;
// 	while (1)
// 	{
// 		pthread_mutex_lock(&data->dead_mutex);
// 		//if (getmillisec() - data->philo[i].last_meal > data->time.time_to_die)
// 		{
// 			pthread_mutex_unlock(&data->dead_mutex);
// 			//print_msg(&data->philo[i], "died");
// 			//data->dead_flag = 1;
// 			break ;
// 		}
// 		if (i == data->num_of_philos)
// 			i = 0;
// 		i++;
// 		pthread_mutex_unlock(&data->dead_mutex);
// 	}
// 	return (NULL);
// }

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
		if (pthread_create(&(*philo)[i].philo_thread, NULL, &philo_thread_start,
				&(*philo)[i]) != 0)
			// fail check
			break ;
		usleep(100);
		i++;
	}
	// i = 0;
	// while (i < data->num_of_philos)
	// {
	// 	pthread_mutex_lock(&data->dead_mutex);
	// 	(*philo)[i].last_meal = data->start_time;
	// 	pthread_mutex_unlock(&data->dead_mutex);
	// 	i++;
	// }
	// monitoring all threads

	// pthread_create(&(*philo)->monitoring_thread, NULL, &start_monitoring,
	// 	data);
	// // // fail check
	// pthread_join((*philo)->monitoring_thread, NULL);

	/// joining the finished threads
	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_join((*philo)[i].philo_thread, NULL) != 0)
			return (print_error("Failed to join threads.\n"),
				ERR_JOINING_THREADS);
		//printf("Thread %d has finished execution.\n", (*philo)[i].philo_id);
		i++;
	}
	// freeing and destroying mutexes
	i = 0;
	while (i < data->num_of_philos)
		pthread_mutex_destroy(&data->fork[i++]);
	pthread_mutex_destroy(&data->printing);
	pthread_mutex_destroy(&data->dead_mutex);
	free((*philo)->data->fork);
	free(*philo);
	return (EXIT_SUCCESS);
}
