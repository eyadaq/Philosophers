/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate_philos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaqrabaw <eaqrabaw@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 06:56:00 by eaqrabaw          #+#    #+#             */
/*   Updated: 2025/05/08 10:37:04 by eaqrabaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int     join_threads(t_data *data, t_philo **philo)
{
    int     i;

    i = 0;
    while (i < data->n_of_philos)
    {
        if (pthread_join(philo[i]->thread, NULL) != 0)
        {
            write(2, "Thread join failed\n", 19);
            cleanup_all(philo, data, data->n_of_philos);
            philo[i]->left_fork = NULL;
            philo[i]->right_fork = NULL;
            return (0);
        }
        i++;
    }
    return (1);
}

int     fill_philo(t_data *data, t_philo **philo, int philo_id)
{
    *philo = malloc(sizeof(t_philo));
    if (!*philo)
    {
        destroy_mutexes(data, data->n_of_philos);
        write(2, "Malloc failed for philosopher\n", 31);
        return (0);
    }
    (*philo)->id = philo_id;
    (*philo)->data = data;
    (*philo)->n_of_meals_eaten = 0;
    (*philo)->last_meal = data->start_time;
    (*philo)->left_fork = &data->forks[philo_id];
    (*philo)->right_fork = &data->forks[(philo_id + 1) % data->n_of_philos];
    return (1);
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

int     init_philos(t_data *data, t_philo **philo)
{
    int     i;

    i = 0;
    if (!init_mutexes(data))
        return (0);
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
            destroy_mutexes(data, i);
            free_threads(philo, i + 1);
            return (0);
        }
        i++;
    }
    if (!join_threads(data, philo))
        return (0);
    return (1);
}
