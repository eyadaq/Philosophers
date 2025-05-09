/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate_philos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaqrabaw <eaqrabaw@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 06:56:00 by eaqrabaw          #+#    #+#             */
/*   Updated: 2025/05/09 05:37:29 by eaqrabaw         ###   ########.fr       */
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
    if (pthread_join(data->monitor_thread, NULL) != 0)
    {
        write(2, "Thread join failed\n", 19);
        cleanup_all(philo, data, data->n_of_philos);
        return (0);
    }
    return (1);
}

int     fill_philo(t_data *data, t_philo **philo, int philo_id)
{
    *philo = malloc(sizeof(t_philo));
    if (!*philo)
    {
        destroy_forks(data, data->n_of_philos);
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
            destroy_forks(data, i);
            write(2, "Mutex creation failed\n", 22);
            return (0);
        }
        i++;
    }
    if (pthread_mutex_init(&data->simulation_lock, NULL) || pthread_mutex_init(&data->print_lock, NULL))
    {
        destroy_forks(data, i);
        write(2, "Mutex creation failed\n", 22);
        return (0);
    }
    return (1);
}

int     init_philos(t_data *data, t_philo **philo)
{
    int     i;

    i = 0;
    data->start_time = get_time();
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
            destroy_forks(data, i);
            free_threads(philo, i + 1);
            return (0);
        }
        i++;
    }
    return (1);
}
