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
//		Odd-ID:
//			Philosophers (P1, P3): Pick up the right fork first,
//				then the left fork.
/////////////////////

static void	routine(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
	}
	print_msg(philo, "is eating");
	usleep(philo->data->time.time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	print_msg(philo, "is sleeping");
	usleep(philo->data->time.time_to_sleep * 1000);
	print_msg(philo, "is thinking");
}

static int	philo_routine_even(t_philo *philo)
{
	int	i;

	if (philo->data->num_of_philos % 2 == 0)
	{
		i = 0;
		while (i < philo->data->num_of_philos)
		{
			routine(philo);
			i++;
		}
	}
	return (EXIT_SUCCESS);
}

int	philo_routine(t_philo *philo)
{
	philo->data->fork = ft_calloc(philo->data->num_of_philos,
			sizeof(pthread_mutex_t));
	if (!philo->data->fork)
		return (ERR_ALLOCATING);
	philo->left_fork = &philo->data->fork[(philo->philo_id - 1)];
	philo->right_fork = &philo->data->fork[(philo->philo_id
			% philo->data->num_of_philos)];
	// printf("\n**********DEBUGING*************\n");
	// printf ("left fork: %d\n", (philo->philo_id - 1
	//		+ philo->data->num_of_philos) % philo->data->num_of_philos);
	// printf ("right fork: %d\n", (philo->philo_id + 1)
	//	% philo->data->num_of_philos);
	// printf("*******************************\n");
	if (philo_routine_even(philo) != EXIT_SUCCESS)
		return (print_error("Failed at routine philo even.\n"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
