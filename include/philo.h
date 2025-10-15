/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abita <abita@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:45:02 by abita             #+#    #+#             */
/*   Updated: 2025/10/14 14:45:05 by abita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILOS_H
# define PHILOS_H
# define ALLOCATING_FAILED 1

# include <stdio.h> // printf() funct
# include <unistd.h> // for sleep funct
# include <pthread.h> // POSIX thread library
# include <stdlib.h> // malloc, free funct
# include "libft.h" // libft helper funct

typedef struct s_philo
{
	pthread_t thread;
	
} t_philo;


#endif
