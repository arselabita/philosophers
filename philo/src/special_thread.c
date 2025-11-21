/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_thread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abita <abita@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 21:21:16 by abita             #+#    #+#             */
/*   Updated: 2025/11/21 21:26:44 by abita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	*special_thread_start(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->right_fork = &philo->data->fork[(philo->philo_id
			% philo->data->num_of_philos)];
	pthread_mutex_lock(philo->right_fork);
	print_msg(philo, "has taken a fork");
	pthread_mutex_unlock(philo->right_fork);
	my_usleep(philo->data->time.time_to_eat, philo);
	return (NULL);
}

void	init_special_thread(t_data *data, t_philo *philo)
{
	int	j;

	if (pthread_create(&philo->philo_thread, NULL, &special_thread_start,
			philo) != 0)
	{
		philo->data->stop_flag = true;
		print_error("Failed to create single thread.\n");
		j = 0;
		while (j < data->num_of_philos)
			pthread_join(philo[j++].philo_thread, NULL);
		return ;
	}
	if (pthread_join(philo->philo_thread, NULL))
		print_error("Failed to join single thread.\n");
}
