/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abita <abita@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 17:45:28 by abita             #+#    #+#             */
/*   Updated: 2025/11/21 21:11:43 by abita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_valid_number(char *str)
{
	int	i;

	if (!str)
		return (EXIT_FAILURE);
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (EXIT_FAILURE);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

void	print_error(const char *msg)
{
	write(STDERR_FILENO, RED, 5);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, RED, 5);
}

void	print_msg(t_philo *philo, char *msg)
{
	char	*color;

	color = RESET_COLOR;
	if (ft_strcmp(msg, "is eating") == 0)
		color = GREEN;
	else if (ft_strcmp(msg, "is sleeping") == 0)
		color = BLUE;
	else if (ft_strcmp(msg, "is thinking") == 0)
		color = YELLOW;
	else if (ft_strcmp(msg, "has taken a fork") == 0)
		color = PURPLE;
	else if (ft_strcmp(msg, "died") == 0)
		color = RED;
	pthread_mutex_lock(&philo->data->printing);
	if (ft_strcmp(msg, "died") == 0)
	{
		philo->data->stop_flag = true;
		printf("%s%ld %d %s\033[0m\n", color, calc_time(philo->data),
			philo->philo_id, msg);
	}
	if (!philo->data->stop_flag)
		printf("%s%ld %d %s\033[0m\n", color, calc_time(philo->data),
			philo->philo_id, msg);
	pthread_mutex_unlock(&philo->data->printing);
}
int	init_forks(t_data *data)
{
	int	i;

	data->fork = ft_calloc(data->num_of_philos, sizeof(pthread_mutex_t));
	if (!data->fork)
		return (ERR_ALLOCATING);
	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_mutex_init(&data->fork[i], NULL) != 0)
		{
			print_error("Failed to initialize forrkk mutex.\n");
			while (i > 0)
				pthread_mutex_destroy(&data->fork[i--]);
			// free(data->fork);
			return (ERR_ALLOCATING);
		}
		i++;
	}
	return(SUCCESS);
}
void	clean_up(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
		pthread_mutex_destroy(&data->fork[i++]);
	if(data->fork)
		free(data->fork);
	pthread_mutex_destroy(&data->printing);
	pthread_mutex_destroy(&data->dead_mutex);
	free(philo);

}
