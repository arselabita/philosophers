/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abita <abita@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 18:06:49 by abita             #+#    #+#             */
/*   Updated: 2025/11/21 18:06:54 by abita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	meal_check(t_philo *philo, int i)
{
	if (philo->data->number_of_times_each_philosopher_must_eat != -1
		&& philo[i].meals_count >= 
		philo->data->number_of_times_each_philosopher_must_eat)
	{
		pthread_mutex_lock(&philo->data->printing);
		philo->data->stop_flag = true;
		pthread_mutex_unlock(&philo->data->printing);
		// break ;
	}
}

static void	*start_monitoring(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	i = 0;
	while (1)
	{
		if (philo->data->stop_flag)
			break ;
		meal_check(philo, i);
		pthread_mutex_lock(&philo->data->dead_mutex);
		if (getmillisec() - philo[i].last_meal > philo->data->time.time_to_die)
		{
			pthread_mutex_unlock(&philo->data->dead_mutex);
			print_msg(&philo[i], "died");
			break ;
		}
		pthread_mutex_unlock(&philo->data->dead_mutex);
		i = (i) % philo->data->num_of_philos;
		usleep(1000);
	}
	return (NULL);
}

void	init_waiter_thread(t_data *data, t_philo *philo)
{
	int	j;

	if (pthread_create(&philo->waiter_thread, NULL, &start_monitoring,
			philo) != 0)
	{
		print_error("Failed to create waiter thread.\n");
		j = 0;
		while (j < data->num_of_philos)
		{
			pthread_join(philo[j].philo_thread, NULL);
			j++;
		}
		free(philo);
	}
}

void	join_waiter_thread(t_data *data, t_philo *philo)
{
	int	j;

	if (pthread_join(philo->waiter_thread, NULL))
	{
		print_error("Failed to join waiter thread.\n");
		j = 0;
		while (j < data->num_of_philos)
		{
			pthread_join(philo[j].philo_thread, NULL);
			j++;
		}
		free(philo);
	}
}
