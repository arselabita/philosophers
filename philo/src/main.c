/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abita <abita@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 11:07:50 by abita             #+#    #+#             */
/*   Updated: 2025/11/21 21:11:03 by abita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_error	result;
	t_data	data;
	t_philo	*philo;

	philo = NULL;
	result = parse_arguments(argc, argv, &data);
	if (result != SUCCESS)
		return (print_error("Error: Failed to parse arguments.\n"),
			ERR_PARSING);
	pthread_mutex_init(&data.printing, NULL);
	pthread_mutex_init(&data.dead_mutex, NULL);
	init_forks(&data);
	data.start_time = getmillisec();
	result = init_run_thread(&data, &philo);
	if (result != SUCCESS)
		return (print_error("Error: Failed to initialize philos.\n"),
			ERR_INVALID_PHILOS);
	return (EXIT_SUCCESS);
}
