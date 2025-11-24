/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abita <abita@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:02:01 by abita             #+#    #+#             */
/*   Updated: 2025/11/21 21:11:35 by abita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	getmillisec(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (print_error("Failed to give time of day.\n"), ERR_GET_TIME);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long	calc_time(t_data *data)
{
	return (getmillisec() - data->start_time);
}

void	my_usleep(uint64_t time, t_philo *philo)
{
	uint64_t	start;

	start = getmillisec();
	if (philo->data->stop_flag)
		return ;
	while (getmillisec() - start < time)
	{
		usleep(500);
	}
}
