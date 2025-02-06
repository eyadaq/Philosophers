/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaqrabaw <eaqrabaw@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:37:06 by eaqrabaw          #+#    #+#             */
/*   Updated: 2025/02/06 08:20:30 by eaqrabaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
static void ft_sub_routine(t_philosopher *philo, t_data *data)
{
    // Debug: Check for valid fork indices
    if (philo->left_fork < 0 || philo->left_fork >= data->num_philo ||
        philo->right_fork < 0 || philo->right_fork >= data->num_philo)
    {
        pthread_mutex_lock(&data->write_lock);
        fprintf(stderr, "Error: Invalid fork indices for philosopher %d: left=%d right=%d\n",
                philo->id, philo->left_fork, philo->right_fork);
        pthread_mutex_unlock(&data->write_lock);
        return;
    }

    print_action(data, philo->id, "is thinking");
    pthread_mutex_lock(&data->forks[philo->left_fork]);
    print_action(data, philo->id, "has taken a fork");
    pthread_mutex_lock(&data->forks[philo->right_fork]);
    print_action(data, philo->id, "has taken a fork");

    pthread_mutex_lock(&data->stop_lock);
    philo->last_meal_time = get_time();
    pthread_mutex_unlock(&data->stop_lock);

    print_action(data, philo->id, "is eating");
    usleep(data->time_to_eat * 1000);
    pthread_mutex_unlock(&data->forks[philo->right_fork]);
    pthread_mutex_unlock(&data->forks[philo->left_fork]);
    print_action(data, philo->id, "is sleeping");
    usleep(data->time_to_sleep * 1000);
}

void *philosopher_routine(void *args)
{
    t_philosopher *philo = (t_philosopher *)args;
    t_data *data = philo->data;

    while (1)
    {
        pthread_mutex_lock(&data->stop_lock);
        if (data->simulation_over)
        {
            pthread_mutex_unlock(&data->stop_lock);
            break;
        }
        pthread_mutex_unlock(&data->stop_lock);
        ft_sub_routine(philo, data);
    }
    return NULL;
}


void monitor_philosophers(t_data *data)
{
    int i;
    
    while (1)
    {
        i = 0;
        while (i < data->num_philo)
        {
            pthread_mutex_lock(&data->stop_lock);
            if (get_time() - data->philosophers[i].last_meal_time > data->time_to_die)
            {
                data->simulation_over = 1;
                // Lock write_lock for safe printing instead of unlocking an unlocked mutex.
                pthread_mutex_lock(&data->write_lock);
                printf("💀 Philosopher %d has died\n", data->philosophers[i].id);
                pthread_mutex_unlock(&data->write_lock);
                pthread_mutex_unlock(&data->stop_lock);
                return;
            }
            pthread_mutex_unlock(&data->stop_lock);
            i++;
        }
        usleep(1000);
    }
}

