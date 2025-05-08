/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaqrabaw <eaqrabaw@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 09:46:43 by eaqrabaw          #+#    #+#             */
/*   Updated: 2025/05/08 11:47:43 by eaqrabaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time(void)
{
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000));
}

void    free_threads(t_philo **philo, int count)
{
    int     i;
    
    i = 0;
    while (i < count)
    {
        pthread_join(philo[i]->thread, NULL);
        free(philo[i]);
        i++;
    }
    free(philo);
    philo = NULL;
}

void    destroy_mutexes(t_data *data, int count)
{
    int     i;
    
    i = 0;
    while (i < count)
    {
        pthread_mutex_destroy(&data->forks[i]);
        i++;
    }
}

void cleanup_all(t_philo **philo, t_data *data, int created)
{
	free_threads(philo, created);
	destroy_mutexes(data, data->n_of_philos);
}
