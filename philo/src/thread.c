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
	run_philo_thread(philo); // here i do sleeping, eating, thinking
	return (NULL);
}

static void	*start_monitoring(void *arg)
{
	t_philo *philo;
	int i;

	philo = (t_philo *)arg;
	i = 0;
	while (1)
	{
		if (philo->data->stop_flag)
			break;
		if(philo->data->number_of_times_each_philosopher_must_eat != -1 && 
			philo[i].meals_count >= philo->data->number_of_times_each_philosopher_must_eat)
		{
			pthread_mutex_lock(&philo->data->printing);
			philo->data->stop_flag = true;
			pthread_mutex_unlock(&philo->data->printing);

			break;
		}
		pthread_mutex_lock(&philo->data->dead_mutex);
		if (getmillisec() - philo[i].last_meal > philo->data->time.time_to_die)
		{
			pthread_mutex_unlock(&philo->data->dead_mutex);
			print_msg(&philo[i], "died");
			break ;
		}
		pthread_mutex_unlock(&philo->data->dead_mutex);
		// move to the next philo
		i = (i) % philo->data->num_of_philos;
		usleep(1000);
	}
	return (NULL);
}

int	init_run_thread(t_data *data, t_philo **philo)
{
	int	i;

	data->stop_flag = false;
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
		// (*philo)[i].meals_count = 0;

		if (pthread_create(&(*philo)[i].philo_thread, NULL, &philo_thread_start,
				&(*philo)[i]) != 0)
		{
			print_error("Failed to create philosopher thread.\n");
			int j = 0;
			while (j < i)
			{
				pthread_join((*philo)[j].philo_thread, NULL);
				j++;
			}
			free(*philo);
			return(ERR_ALLOCATING);
		}
		i++;
	}
	usleep(1);
	// monitoring all threads
	if (pthread_create(&(*philo)->monitoring_thread, NULL, &start_monitoring, (*philo)) != 0)
		return (print_error("Failed to create monitoring thread.\n"), ERR_ALLOCATING);
	/// joining the finished threads
	
	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_join((*philo)[i].philo_thread, NULL) != 0)
		{
			int j = 0;
			while (j < data->num_of_philos)
			{
				pthread_join((*philo)[j].philo_thread, NULL);
				j++;
			}
				i = 0;
	// while (i < data->num_of_philos)
	// 	pthread_mutex_destroy(&data->fork[i++]);
	// free(data->fork);
	// pthread_mutex_destroy(&data->printing);
	// pthread_mutex_destroy(&data->dead_mutex);
			free(*philo);
			return(ERR_JOINING_THREADS);
		}
		i++;
	}

	if (pthread_join((*philo)->monitoring_thread, NULL))
		return (print_error("Failed to join monitoring thread.\n"), ERR_JOINING_THREADS);
	// freeing and destroying mutexes
	i = 0;
	while (i < data->num_of_philos)
		pthread_mutex_destroy(&data->fork[i++]);
	free(data->fork);
	pthread_mutex_destroy(&data->printing);
	pthread_mutex_destroy(&data->dead_mutex);
	free(*philo);
	return (EXIT_SUCCESS);
}
