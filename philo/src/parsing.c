/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abita <abita@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 11:36:32 by abita             #+#    #+#             */
/*   Updated: 2025/10/27 11:36:33 by abita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	parsing_helper(char *nums, int *number)
{
	long	value;

	if (ft_valid_number(nums) == EXIT_FAILURE)
	{
		print_error("parsing_helper: Invalid numeric value.\n");
		return (EXIT_FAILURE);
	}
		
	value = ft_atol(nums);
	if (value < INT_MIN || value > INT_MAX)
	{
		print_error("parsing_helper: integer overflow or underflow.\n");
		return (EXIT_FAILURE);
	}
	*number = (int)value;
	return (EXIT_SUCCESS);
}

int	parse_arguments(int argc, char **argv, t_data *data)
{
	int		i;
	int		number;

	i = 1;
	while (i < argc)
	{
		if (parsing_helper(argv[1], &number))
			return (EXIT_FAILURE);
		data->num_of_philos = number;
		if (parsing_helper(argv[2], &number))
			return (EXIT_FAILURE);
		data->time.time_to_die = number;
		if (parsing_helper(argv[3], &number))
			return (EXIT_FAILURE);
		data->time.time_to_eat = number;
		if (parsing_helper(argv[4], &number))
			return (EXIT_FAILURE);
		data->time.time_to_sleep = number;
		i++;
	}
	if (argc == 6)
	{
		if (parsing_helper(argv[5], &number))
			return (EXIT_FAILURE);
		data->number_of_times_each_philosopher_must_eat = number;
	}
	else
		data->number_of_times_each_philosopher_must_eat = -1;

	printf("**********DEBUGING*************\n");
	printf (" num of philos: %d\n time to die: %d\n time to eat: %d\n time to sleep: %d\n num of times ph eat: %d\n", data->num_of_philos, data->time.time_to_die, data->time.time_to_eat, data->time.time_to_sleep, data->number_of_times_each_philosopher_must_eat);
	printf("*******************************\n");
	
	
	if (data->num_of_philos <= 0 || data->time.time_to_die <= 0 \
		|| data->time.time_to_eat <= 0 || data->time.time_to_sleep <= 0)
		{
			print_error("Error: All arguments must be greater than 0.\n");
			return (EXIT_FAILURE);
		}
	if (argc == 6 && data->number_of_times_each_philosopher_must_eat <= 0)
	{
		print_error("Error: number_of_times_each_philosopher_must_eat must be > than 0.\n");
		return (EXIT_FAILURE);
	}		
	return (EXIT_SUCCESS);
}
/*
	if (argc != 2)
		return (EXIT_FAILURE);
	if ((philo. = ft_atoi(argv[1])) <= 0)
		return(perror("Invalid number of philosophers.\n"), INVALID_PHILOS);
	*philo = ft_calloc(data->conv_to_num, sizeof(t_philo));
	if (!philo)
		return (ERR_ALLOCATING);
*/