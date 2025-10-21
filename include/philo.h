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
# define ALLOCATING_FAILED 2
# define INVALID_PHILOS 1
# define FAILED_CREATING_THREADS 3
# define FAILED_JOINING_THREADS 4

# include <stdio.h> // printf() funct
# include <unistd.h> // for sleep funct
# include <pthread.h> // POSIX thread library
# include <stdlib.h> // malloc, free funct

typedef struct s_philo
{
	pthread_t *thread;
	
} t_philo;


#endif
