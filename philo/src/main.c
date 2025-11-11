/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abita <abita@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 11:07:50 by abita             #+#    #+#             */
/*   Updated: 2025/10/27 11:36:43 by abita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/////////////////////
// the dining philosophers problem is an example problem
// often used in concurrent algorithm design to illustrate synchronization
// issues and techniques for resolving them.
/////////////////////

int	main(int argc, char **argv)
{
	t_error	result;
	t_data	data ;
	t_philo	*philo;

	philo = NULL;
	if (argc < 5 || argc > 6)
	{
		print_error("Error: Invalid number of arguments.\n");
		print_error("Usage: ./philo [number_of_philosophers] [time_to_die] \
			[time_to_eat] [time_to_sleep] \
			[number_of_times_each_philosopher_must_eat]\n");
		return (EXIT_FAILURE);
	}
	result = parse_arguments(argc, argv, &data);
	if (result != SUCCESS)
		return (print_error("Error: Failed to parse arguments.\n"),
			ERR_PARSING);
	pthread_mutex_init(&data.printing, NULL);
	pthread_mutex_init(&data.dead_mutex, NULL);
	data.fork = ft_calloc(data.num_of_philos,
			sizeof(pthread_mutex_t));
	if (!data.fork)
		return (ERR_ALLOCATING);
	data.start_time = getmillisec();
	result = init_run_thread(&data, &philo);
	if (result != SUCCESS)
		return (print_error("Error: Failed to initialize philos.\n"),
			ERR_INVALID_PHILOS);
	return (EXIT_SUCCESS);
}
