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
#include <unistd.h>
#include <pthread.h> // POSIX thread library

// playing around with threads
// how to create a thread? -> we are going to use 



// void *myturn(void *arg)
// {
// 	int i = 0;
// 	while (i < 8)
// 	{
// 		sleep(2);
// 		printf("My Turn! %d\n", i);
// 		i++;
// 	}
// 	return NULL;
// }

// void yourturn()
// {
// 	int i = 0;
// 	while (i < 5)
// 	{
// 		sleep(2);
// 		printf("Your Turn! %d\n", i);
// 		i++;
// 	}
// }
// int main()
// {
// 	pthread_t newThread;

// 	pthread_create(&newThread, NULL, myturn, NULL);
// 	// myturn();
// 	yourturn();
// 	// wait until the thread is done
// 	pthread_join(newThread, NULL);
// 	return (0);
// }


/////////////////////////////////////////////////////////////

// int mails = 0;
// pthread_mutex_t mutex;

// void *rutine()
// {
// 	// printf("Test from threads\n");
// 	// sleep(3);
// 	// printf("Ending thread\n");
// 	// return NULL;
 
// 	int i = 0;
// 	while (i < 1000000)
// 	{
// 		pthread_mutex_lock(&mutex);
// 		mails++;
// 		i++;
// 		pthread_mutex_unlock(&mutex);
// 		// read the mails
// 		// increment
// 		// write mails
// 	}
// 	return NULL;

// }

// int main(int ac, char **av)
// {
// 	pthread_t thread1;
// 	pthread_t thread2;
// 	pthread_mutex_init(&mutex, NULL);

// 	if (pthread_create(&thread1, NULL, &rutine, NULL) != 0)
// 		return 1;
// 	if (pthread_create(&thread2, NULL, &rutine, NULL) != 0)
// 		return 2;
// 	// wait until it has finished executing
// 	if (pthread_join(thread1, NULL) != 0)
// 		return 3;
// 	if (pthread_join(thread2, NULL) != 0)
// 		return 4;
// 	pthread_mutex_destroy(&mutex);
// 	printf("Number of mails: %d\n", mails);
// 	return (0);
// }



///////////////////////////////////////////////////////////


// void *computation(void *add)
// {
// 	long sum = 0;
// 	long i = 0;
// 	long *add_num = (long *) (add);

// 	while (i < 1000000000)
// 	{
// 		sum += *add_num;
// 		i++;
// 	}

// 	printf("Add: %ld\n", *add_num);
// 	return (NULL);
// }


// int main()
// {
// 	pthread_t thread1;
// 	pthread_t thread2;
// 	long value1 = 1;
// 	long value2 = 2;

// 	pthread_create(&thread1, NULL, computation, (void *) &value1);
// 	pthread_join(thread1, NULL);

// 	pthread_create(&thread2, NULL, computation, (void *) &value2);	
// 	pthread_join(thread2, NULL);

// 	/* computation((void *) &value1);
// 	computation((void *) &value2); */
// 	return (0);
// }


