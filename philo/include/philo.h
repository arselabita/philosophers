/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abita <abita@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:45:02 by abita             #+#    #+#             */
/*   Updated: 2025/10/27 11:37:03 by abita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOS_H
# define PHILOS_H
# define ERR_ALLOCATING 1
# define INVALID_PHILOS 1
# define ERR_CREATING_THREADS 1
# define ERR_JOINING_THREADS 1
# define ERR_PHILOS_FUNCT 1
# define ERR_GET_TIME 1
# define ERR_PARSING 1

# include <stdio.h> // printf() funct
# include <unistd.h> // for sleep funct
# include <pthread.h> // POSIX thread library
# include <stdlib.h> // malloc, free funct
# include <limits.h> // size_t, INT_MAX, INT_MIN
# include <stdint.h> // SIZE_MAX
# include <sys/time.h> // gettimeofday

typedef struct s_data t_data;
typedef struct s_time t_time;
typedef struct s_philo t_philo;

// time related values in here
typedef struct s_time
{
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
} t_time;

// all global simulation settings
typedef struct s_data
{
	int num_of_philos;
	int number_of_times_each_philosopher_must_eat;
	long start_time;
	pthread_mutex_t printing;
	pthread_mutex_t *fork;
	t_time time;
} t_data;

// and the philo struct
typedef struct s_philo
{
	pthread_t philo_thread;
	int philo_id;
	int not_dead;
	pthread_mutex_t *right_fork;
	pthread_mutex_t *left_fork;
	t_data *data;

} t_philo;

// utils
void	*ft_calloc(size_t count, size_t size);
long long	ft_atol(const char *nptr);
void	ft_bzero(void *s, size_t n);
int		ft_valid_number(char *str);
void	print_error(const char *msg);
void 	print_msg(t_philo *philo, char *msg);

// parsing
int 	parse_arguments(int argc, char **argv, t_data *data);

// simulation
int 	init_run_thread(t_data *data, t_philo **philo);
int		philo_monitoring(t_philo *philo);

// time
long	getmillisec();
long 	calc_time(t_data *data);

#endif
