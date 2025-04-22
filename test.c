/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaqrabaw <eaqrabaw@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 07:31:42 by eaqrabaw          #+#    #+#             */
/*   Updated: 2025/04/22 07:59:39 by eaqrabaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
// Create 5 threads that print a message ->

void 	*routine(void *p)
{
	printf("%s\n", "Hello from thread num:");
}
int main() {
   
	int 	n_threads = 5;
	pthread_t  *threads;

	threads = malloc(sizeof(pthread_t) * n_threads);
	for(int i = 0; i < n_threads; i++)
	{
		pthread_create(&threads[i], NULL, routine, NULL);
	}
	for(int j = 0; j < n_threads; j++)
	{
		pthread_join(&threads[i], NULL);
	}
    return (0);
}
