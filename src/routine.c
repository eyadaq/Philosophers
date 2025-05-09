/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaqrabaw <eaqrabaw@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 07:26:42 by eaqrabaw          #+#    #+#             */
/*   Updated: 2025/05/09 05:39:08 by eaqrabaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int is_dead(t_philo *philo)
{
	return ((get_time() - philo->last_meal) > philo->data->t_t_die);
}


void    ft_print(t_philo *philo, char *str)
{
    pthread_mutex_lock(&philo->data->print_lock);
    printf("%ld %d %s\n", (long)(get_time() - philo->data->start_time), philo->id + 1, str);
    pthread_mutex_unlock(&philo->data->print_lock);
}

void    ft_eat(t_philo *philo)
{
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(philo->left_fork);
        ft_print(philo, "has taken left fork");
        pthread_mutex_lock(philo->right_fork);
        ft_print(philo, "has taken right fork");
    }
    else
    {
        pthread_mutex_lock(philo->right_fork);
        ft_print(philo, "has taken right fork");
        pthread_mutex_lock(philo->left_fork);
        ft_print(philo, "has taken left fork");
    }
    philo->last_meal = get_time();
    ft_print(philo, "is eating");
    usleep(philo->data->t_t_eat * 1000);
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}

int is_dead(t_philo *philo)
{
	return ((get_time() - philo->last_meal) > philo->data->t_t_die);
}

void    *routine(void *arg)
{
    t_philo	*philo;
    int stop;
    philo = (t_philo *)arg;
    
    while (philo->data->must_eat == -1 || philo->n_of_meals_eaten < philo->data->must_eat)
    {
        pthread_mutex_lock(&philo->data->simulation_lock);
        stop = philo->data->stop_simulation;
        pthread_mutex_unlock(&philo->data->simulation_lock);
        if (stop)
            break;
        ft_eat(philo);
        philo->n_of_meals_eaten++;
        ft_print(philo, "is sleeping");
        usleep(philo->data->t_t_sleep * 1000);
        ft_print(philo, "is thinking");
        usleep(100);
    }
    return (NULL);
}