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

// static int philo_routine_even(t_philo *philo)
// {
// 	if (philo->data->num_of_philos % 2 == 0)
// 	{
		 
// 	}
// 	return (EXIT_SUCCESS);
// }

int philo_routine(t_philo *philo)
{
	philo->left_fork = &philo->data->fork[((philo->philo_id - 1 + philo->data->num_of_philos) % philo->data->num_of_philos)];
	philo->right_fork = &philo->data->fork[((philo->philo_id + 1) % philo->data->num_of_philos)];

	printf("\n**********DEBUGING*************\n");
	printf ("left fork: %d\n", (philo->philo_id - 1 + philo->data->num_of_philos) % philo->data->num_of_philos);
	printf ("right fork: %d\n", (philo->philo_id + 1) % philo->data->num_of_philos);
	printf("*******************************\n");

	// if (philo_routine_even(philo) != EXIT_SUCCESS)
	// 	return (print_error("Failed at routine philo even.\n"), EXIT_FAILURE);
	

	return (EXIT_SUCCESS);
}
