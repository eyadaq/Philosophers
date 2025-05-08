/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate_philos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaqrabaw <eaqrabaw@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 06:56:00 by eaqrabaw          #+#    #+#             */
/*   Updated: 2025/05/08 08:34:16 by eaqrabaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

int     fill_philo(t_data *data, t_philo **philo, int philo_id)
{
    *philo = malloc(sizeof(t_philo));
    if (!*philo)
    {
        write(2, "Malloc failed for philosopher\n", 31);
        return (0);
    }
    (*philo)->id = philo_id;
    (*philo)->data = data;
    (*philo)->n_of_meals_eaten = 0;
    (*philo)->last_meal = data->start_time;
    return (1);
}

int init_philos(t_data *data, t_philo **philo)
{
    int     i;

    i = 0;
    while (i < data->n_of_philos)
    {
        if(!fill_philo(data, &philo[i], i))
        {
            free_threads(philo, i);
            return (0);
        }
        if (pthread_create(&philo[i]->thread, NULL, routine, philo[i]))
        {
            write(2, "Thread creation failed\n", 24);
            free_threads(philo, i + 1);
            return (0);
        }
        i++;
    }
    i = 0;
    while (i < data->n_of_philos)
    {
        pthread_join(philo[i]->thread, NULL);
        i++;
    }
    return (1);
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

int     init_mutexes(t_data *data)
{
    int     i;

    i = 0;
    while (i < data->n_of_philos)
    {
        if (pthread_mutex_init(&data->forks[i], NULL))
        {
            destroy_mutexes(data, i);
            write(2, "Mutex creation failed\n", 22);
            return (0);
        }
        i++;
    }
    return (1);
}