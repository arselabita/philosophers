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
	run_philo_thread(philo);
	return (NULL);
}

static void	init_philos_thread(t_data *data, t_philo *philo)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->num_of_philos)
	{
		philo[i].philo_id = i + 1;
		philo[i].data = data;
		pthread_mutex_lock(&data->dead_mutex);
		philo[i].last_meal = data->start_time;
		pthread_mutex_unlock(&data->dead_mutex);
		if (pthread_create(&philo[i].philo_thread, NULL, &philo_thread_start,
				&(philo)[i]) != 0)
		{
			print_error("Failed to create philosopher thread.\n");
			j = 0;
			while (j < i)
				pthread_join(philo[j++].philo_thread, NULL);
			free(philo);
		}
		i++;
	}
	usleep(1);
}

static void	join_philo_thread(t_data *data, t_philo *philo)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_join(philo[i].philo_thread, NULL) != 0)
		{
			j = 0;
			while (j < data->num_of_philos)
			{
				pthread_join(philo[j].philo_thread, NULL);
				j++;
			}
			free(philo);
		}
		i++;
	}
}

int	init_run_thread(t_data *data, t_philo **philo)
{
	data->stop_flag = false;
	*philo = ft_calloc(data->num_of_philos, sizeof(t_philo));
	if (!*philo)
		return (ERR_ALLOCATING);
	data->philo = *philo;
	init_philos_thread(data, *philo);
	init_waiter_thread(data, *philo);
	join_philo_thread(data, *philo);
	join_waiter_thread(data, *philo);
	clean_up(data, *philo);
	return (EXIT_SUCCESS);
}
