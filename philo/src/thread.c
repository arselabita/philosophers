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
static void	*monitoring_thread(void *arg)
{
	t_philo	*philo;

	while (*philo->dead != -1)
	{
		if (getmillisec() - philo->last_meal > philo->data->time.time_to_die)
		{
			print_msg(philo, "died");
			*philo->dead = -1;
			break ;
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
		if (pthread_create(&(*philo)[i].philo_thread, NULL, &philo_thread_start,
				&(*philo)[i]) != 0)
			return (print_error("Failed to creating threads.\n"),
				ERR_JOINING_THREADS);
		usleep(100);
		i++;
	}
	if (pthread_create(&(*philo)[i].monitoring_thread, NULL, &monitoring_thread,
			&(*philo)) != 0)
		;
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
