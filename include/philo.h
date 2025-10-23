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
# define INVALID_PHILOS 1
# define FAILED_CREATING_THREADS 1
# define FAILED_JOINING_THREADS 1
# define ERR_PHILOS_FUNCT 1

# include <stdio.h> // printf() funct
# include <unistd.h> // for sleep funct
# include <pthread.h> // POSIX thread library
# include <stdlib.h> // malloc, free funct

typedef struct s_mutex
{
	pthread_mutex_t printing;
} t_mutex;

typedef struct s_philo
{
	int index;
	pthread_t thread;
	t_mutex mutex;
} t_philo;



#endif
