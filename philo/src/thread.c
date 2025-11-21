/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abita <abita@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 12:35:34 by abita             #+#    #+#             */
/*   Updated: 2025/11/21 21:11:28 by abita            ###   ########.fr       */
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
		philo[i].meals_count = 0;
		pthread_mutex_lock(&data->dead_mutex);
		philo[i].last_meal = data->start_time;
		pthread_mutex_unlock(&data->dead_mutex);
		if (pthread_create(&philo[i].philo_thread, NULL, &philo_thread_start,
				&(philo)[i]) != 0)
		{
			philo->data->stop_flag = true;
			data->join_check = true;
			print_error("Failed to create philosopher thread.\n");
			j = 0;
			while (j < i)
				pthread_join(philo[j++].philo_thread, NULL);
			return ;
		}
		i++;
	}
}

static void	join_philo_thread(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_join(philo[i].philo_thread, NULL) != 0)
		{
			print_error("Failed to join philosopher thread.\n");
			return ;
		}
		i++;
	}
}

int	init_run_thread(t_data *data, t_philo **philo)
{
	data->stop_flag = false;
	data->join_check = false;
	*philo = ft_calloc(data->num_of_philos, sizeof(t_philo));
	if (!*philo)
		return (ERR_ALLOCATING);
	data->philo = *philo;
	if (data->num_of_philos == 1)
	{
		(*philo)[0].philo_id = 1;
		(*philo)[0].data = data;
		(*philo)[0].meals_count = 0;
		pthread_mutex_lock(&data->dead_mutex);
		(*philo)[0].last_meal = data->start_time;
		pthread_mutex_unlock(&data->dead_mutex);
		init_special_thread(data, *philo);
		data->join_check = true;
	}
	else
		init_philos_thread(data, *philo);
	init_join_waiter_thread(data, *philo);
	if (!data->join_check)
		join_philo_thread(data, *philo);
	clean_up(data, *philo);
	return (EXIT_SUCCESS);
}
