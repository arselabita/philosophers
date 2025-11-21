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

static int	parsing_helper(char *nums, int *number) // check for overflowing
{
	long value;

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
	return (SUCCESS);
}

static int	arg_check(int argc, char **argv, int number, t_data *data)
{
	if (argc == 6)
	{
		if (parsing_helper(argv[5], &number) != SUCCESS)
			return (EXIT_FAILURE);
		data->number_of_times_each_philosopher_must_eat = number;
	}
	else
		data->number_of_times_each_philosopher_must_eat = -1;
	if (data->num_of_philos <= 0 || data->num_of_philos > 200
		|| data->time.time_to_die <= 0 || data->time.time_to_eat <= 0
		|| data->time.time_to_sleep <= 0)
	{
		print_error("Error: All arguments must be greater than 0 or greater than 200 \
			for num of philos.\n");
		return (EXIT_FAILURE);
	}
	if (argc == 6 && data->number_of_times_each_philosopher_must_eat < 0)
	{
		print_error("Error: number_of_times_each_philosopher_must_eat must be > than\
			-1.\n");
		return (EXIT_FAILURE);
	}
	return (SUCCESS);
}

static int	give_values(int argc, char **argv, t_data *data)
{
	int	i;
	int	number;

	i = 1;
	memset(data, 0, sizeof(t_data));
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
	if (arg_check(argc, argv, number, data) != SUCCESS)
		return (EXIT_FAILURE);
	return (SUCCESS);
}
int parse_arguments(int argc, char **argv, t_data *data)
{
	if (argc < 5 || argc > 6)
	{
		print_error("Error: Invalid number of arguments.\n");
		print_error("Usage: ./philo [number_of_philosophers] [time_to_die] \
			[time_to_eat] [time_to_sleep] \
			[number_of_times_each_philosopher_must_eat]\n");
		return (EXIT_FAILURE);
	}
	if (give_values(argc, argv, data) != SUCCESS)
		return (EXIT_FAILURE);
	return (SUCCESS);
}
