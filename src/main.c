/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abita <abita@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 11:07:50 by abita             #+#    #+#             */
/*   Updated: 2025/09/29 11:07:51 by abita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// playing around with threads
// how to create a thread? -> we are going to use 

int main(int argc, char **argv)
{
	t_philo *philos;
	int conv_philos_num;
	int i;

	if (argc != 2)
		return (EXIT_FAILURE);
	conv_philos_num = ft_atoi(argv[1]);
	philos = ft_calloc(conv_philos_num, sizeof(t_philo));
	if (!philos)
		return (ALLOCATING_FAILED);
	


	return (0);
}
	// pthread_t thread1;
	// pthread_t thread2;
	// pthread_mutex_init(&mutex, NULL);

	// if (pthread_create(&thread1, NULL, &rutine, NULL) != 0)
	// 	return 1;
	// if (pthread_create(&thread2, NULL, &rutine, NULL) != 0)
	// 	return 2;
	// // wait until it has finished executing
	// if (pthread_join(thread1, NULL) != 0)
	// 	return 3;
	// if (pthread_join(thread2, NULL) != 0)
	// 	return 4;
	// pthread_mutex_destroy(&mutex);
	// printf("Number of mails: %d\n", mails);