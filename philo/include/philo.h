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

# define GREEN "\033[32m"
# define BLUE "\033[34m"
# define YELLOW "\033[33m"
# define PURPLE "\033[36m"
# define RED "\033[31m"
# define RESET_COLOR "\033[0m"

# include <limits.h>    // size_t, INT_MAX, INT_MIN
# include <pthread.h>   // POSIX thread library
# include <stdatomic.h> // forr atomics
# include <stdbool.h>   // bool
# include <stdint.h>    // SIZE_MAX
# include <stdio.h>     // printf() funct
# include <stdlib.h>    // malloc, free funct
# include <string.h>    // memset
# include <sys/time.h>  // gettimeofday
# include <unistd.h>    // for sleep funct

typedef struct s_data	t_data;
typedef struct s_time	t_time;
typedef struct s_philo	t_philo;

// time related values in here
typedef struct s_time
{
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
}						t_time;

// all global simulation settings
typedef struct s_data
{
	int					num_of_philos;
	int					number_of_times_each_philosopher_must_eat;
	long				start_time;
	_Atomic bool 		stop_flag;
	pthread_mutex_t		dead_mutex;
	pthread_mutex_t		printing;
	pthread_mutex_t		*fork;
	t_time				time;
	t_philo				*philo;
}						t_data;

// and the philo struct
typedef struct s_philo
{
	int					philo_id;
	pthread_t			philo_thread;
	_Atomic int 		meals_count;
	long				last_meal;
	pthread_t			monitoring_thread;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*left_fork;
	t_data				*data;
}						t_philo;

// enum for all the errors
typedef enum e_error
{
	SUCCESS = 0,
	ERR_ALLOCATING,
	ERR_INVALID_PHILOS,
	ERR_CREATING_THREADS,
	ERR_JOINING_THREADS,
	ERR_PHILOS_FUNCT,
	ERR_GET_TIME,
	ERR_PARSING,
	DEAD = -1
}						t_error;

// utils
void					*ft_calloc(size_t count, size_t size);
long long				ft_atol(const char *nptr);
void					ft_bzero(void *s, size_t n);
int						ft_valid_number(char *str);
void					print_error(const char *msg);
void					print_msg(t_philo *philo, char *msg);
int						ft_strcmp(char *s1, char *s2);

// parsing
int						parse_arguments(int argc, char **argv, t_data *data);

// simulation
int						init_run_thread(t_data *data, t_philo **philo);
int						run_philo_thread(t_philo *philo);

// time
long					getmillisec(void);
long					calc_time(t_data *data);
void					my_usleep(uint64_t time);

#endif
