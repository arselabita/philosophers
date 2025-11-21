/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abita <abita@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:01:44 by abita             #+#    #+#             */
/*   Updated: 2025/11/04 14:01:45 by abita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/////////////////////
// Fork Acquisition Order:
//
//	For Example:
//		Even-ID:
//			Philosophers (P0, P2): Pick up the left fork first,
//				then the right fork.
//	Odd-ID:
//			Philosophers (P1, P3): Pick up the right fork first,
//				then the left fork.
/////////////////////

static void	take_forks(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_msg(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_msg(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_msg(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_msg(philo, "has taken a fork");
	}
}
static void	help(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->printing);
	take_forks(philo);
	pthread_mutex_lock(&philo->data->dead_mutex);
	philo->last_meal = getmillisec();
	pthread_mutex_unlock(&philo->data->dead_mutex);
	print_msg(philo, "is eating");
	philo->meals_count++;
	my_usleep(philo->data->time.time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	print_msg(philo, "is sleeping");
	my_usleep(philo->data->time.time_to_sleep);
	if (philo->data->num_of_philos % 2 != 0)
	{
		print_msg(philo, "is thinking");
		my_usleep(philo->data->time.time_to_eat * 2
			- philo->data->time.time_to_sleep);
	}
	else
	{
		print_msg(philo, "is thinking");
		my_usleep(1);
	}
}
static int	philo_routine(t_philo *philo)
{
	int	i;

	i = 0;
	if (philo->philo_id % 2 != 0)
		my_usleep(philo->data->time.time_to_eat);
	pthread_mutex_lock(&philo->data->printing);
	while (!philo->data->stop_flag
		&& ((philo->data->number_of_times_each_philosopher_must_eat == -1)
			|| i <= philo->data->number_of_times_each_philosopher_must_eat))
	{
		help(philo);
		i++;
		pthread_mutex_lock(&philo->data->printing);
	}
	pthread_mutex_unlock(&philo->data->printing);
	return (SUCCESS);
}

int	run_philo_thread(t_philo *philo)
{
	philo->left_fork = &philo->data->fork[(philo->philo_id - 1)];
	philo->right_fork = &philo->data->fork[(philo->philo_id
			% philo->data->num_of_philos)];
	if (philo_routine(philo) != SUCCESS)
		return (print_error("Failed at routine philo even.\n"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
