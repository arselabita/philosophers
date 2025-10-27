/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abita <abita@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 12:35:34 by abita             #+#    #+#             */
/*   Updated: 2025/10/27 12:35:35 by abita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include "../include/philo.h"

static int getmillisec()
{
	struct timeval tv;
	if (gettimeofday(&tv, NULL) == -1)
		return (perror("Failed to give time of day.\n"), ERR_GET_TIME);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	// Convering seconds to milliseconds and microseconds too
}

static void *start_routine(void *arg)
{
	t_philo *philo;
	int millisec;

	millisec = getmillisec();
	printf("%d ", millisec);



	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->printing);
	printf("Philosofer %zu\n", philo->philo_id);
	pthread_mutex_unlock(&philo->printing);

	// printf("Philosopher %zu is thinking.\n", philo->philo_id);	
	// printf("Philosopher %zu has taken a fork.\n", philo->philo_id);
	// printf("Philosopher %zu is eating.\n", philo->philo_id);
	// printf("Philosopher %zu has finished.\n", philo->philo_id);
	
	return (NULL);
}
static void run_threads(t_data data, t_philo *philo)
{
	int i;

	i = 0;
	while (i < data.conv_to_num)
	{
		if (pthread_join(philo[i].thread, NULL) != 0) // waits for all threads to finish
			return (perror("Failed to join threads.\n"), ERR_JOINING_THREADS);
		printf("Thread %zu has finished execution.\n", philo[i].philo_id);
		i++;
	}
}
static void free_destroy(t_philo *philo)
{
	int i = 0;

	while (i < data)
	pthread_mutex_destroy(&philo->printing);
	free(philo);
}
void init_run_thread(t_data *data, t_philo *philo)
{
	int i;

	i = 0;
	pthread_mutex_init(&philo->printing, NULL);
	while (i < data->conv_to_num)
	{
		philo[i].philo_id = i + 1;
		if(pthread_create(&philo[i].thread, NULL, &start_routine, &philo[i]) != 0)
			return (perror("Failed to create thread.\n"), ERR_CREATING_THREADS);
		usleep(100);
		i++;
	}
	run_threads(data, philo);
	free_destroy(philo);
	return (0);
} */

