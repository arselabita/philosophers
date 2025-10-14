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

#include <stdio.h>
#include <pthread.h> // POSIX thread library

// playing around with threads
// how to create a thread? -> we are going to use 

void *computation()
{
	printf("Computation\n");
	return (NULL);
}


int main()
{
	pthread_t thread1;
	pthread_create(&thread1, NULL, computation, NULL);
	return (0);
}