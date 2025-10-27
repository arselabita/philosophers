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

static int	arg_count(int argc, char **argv)
{
	int		i;
	int		j;
	int		count;
	char	**split;

	i = 1;
	count = 0;
	while (i < argc)
	{
		split = ft_split(argv[i], ' ');
		if (!split)
		{
			perror("arg_count: memory allocation failed during split.\n");
			return (EXIT_FAILURE);
		}	
		j = 0;
		while (split[j])
		{
			count++;
			j++;
		}
		free_split(split);
		i++;
	}
	return (count);
}

static int	parsing_helper(char *nums, int *number)
{
	long	value;

	if (ft_valid_number(nums) == EXIT_FAILURE)
	{
		perror("parsing_helper: Invalid numeric value.\n");
		return (EXIT_FAILURE);
	}
		
	value = ft_atol(nums);
	if (value < INT_MIN || value > INT_MAX)
	{
		perror("parsing_helper: integer overflow or underflow.\n");
		return (EXIT_FAILURE);
	}
	*number = (int)value;
	return (EXIT_SUCCESS);
}

int	parse_arguments(int argc, char **argv, t_data *data)
{
	int		i;
	int		j;
	int		number;
	char	**nums;
	int		argument_count;

	argument_count = arg_count(argc, argv);
	if (argument_count == 0)
		return (write(2, "ERROR\n", 6), 1);
	i = 1;
	while (i < argc)
	{
		nums = ft_split(argv[i], ' ');
		if (!nums)
			return (perror("parse_arguments: split failed.\n"), EXIT_FAILURE);
		j = 0;
		while (nums[j])
		{
			if (parsing_helper(nums[j], &number))
				return (free_split(nums), EXIT_FAILURE);
			j++;
		}
		if (i == 1)
			data->num_of_philos = number;
		else if(i == 2)
			data->time.time_to_die = number;
		else if(i == 3)
			data->time.time_to_eat = number;
		else if(i == 4)
			data->time.time_to_sleep = number;
		else if(i == 5)
			data->number_of_times_each_philosopher_must_eat = number;
		free_split(nums);
		i++;
	}
	if (argc == 5)
		data->number_of_times_each_philosopher_must_eat = -1;
	printf ("num of philos: %d\n time to die: %d\n time to eat: %d\n \
			time to sleep: %d\n num of times ph eat: %d\n", data->num_of_philos, data->time.time_to_die, data->time.time_to_eat, data->time.time_to_sleep, data->number_of_times_each_philosopher_must_eat);
	if (data->num_of_philos <= 0 || data->time.time_to_die <= 0 \
		|| data->time.time_to_eat <= 0 || data->time.time_to_sleep <= 0)
		{
			write(STDERR_FILENO, "Error: All arguments must be greater than 0.\n", 45);
			return (EXIT_FAILURE);
		}
	if (argc == 6 && data->number_of_times_each_philosopher_must_eat <= 0)
	{
		write(STDERR_FILENO, "Error: number_of_times_each_philosopher_must_eat must be > than 0.\n", 45);
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