/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abita <abita@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 18:06:49 by abita             #+#    #+#             */
/*   Updated: 2025/11/21 21:11:55 by abita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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
		if (philo->data->number_of_times_each_philosopher_must_eat != -1
			&& philo[i].meals_count == \
			philo->data->number_of_times_each_philosopher_must_eat)
			break ;
		pthread_mutex_lock(&philo->data->dead_mutex);
		if (getmillisec() - philo[i].last_meal > philo->data->time.time_to_die)
		{
			pthread_mutex_unlock(&philo->data->dead_mutex);
			print_msg(&philo[i], "died");
			break ;
		}
		pthread_mutex_unlock(&philo->data->dead_mutex);
		i = (i + 1) % philo->data->num_of_philos;
	}
	return (NULL);
}

void	init_join_waiter_thread(t_data *data, t_philo *philo)
{
	int	j;

	if (pthread_create(&philo->waiter_thread, NULL, &start_monitoring,
			philo) != 0)
	{
		philo->data->stop_flag = true;
		print_error("Failed to create waiter thread.\n");
		j = 0;
		while (j < data->num_of_philos)
			pthread_join(philo[j++].philo_thread, NULL);
		return ;
	}
	if (pthread_join(philo->waiter_thread, NULL))
		print_error("Failed to join waiter thread.\n");
}
