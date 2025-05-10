/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaqrabaw <eaqrabaw@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 07:26:42 by eaqrabaw          #+#    #+#             */
/*   Updated: 2025/05/10 03:06:34 by eaqrabaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void		ft_eat_helper(t_philo *philo)
{
	long start_eating_time;
	long current_time;
	long elapsed_eating_time;
	
	pthread_mutex_lock(&philo->data->simulation_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->data->simulation_lock);
	ft_print(philo, "is eating");
	start_eating_time = get_time();
	while (should_continue(philo))
	{
		current_time = get_time();
		elapsed_eating_time = current_time - start_eating_time;
		if (elapsed_eating_time >= philo->data->t_t_eat)
			break;
		usleep(5000);
	}
	if (should_continue(philo))
		philo->n_of_meals_eaten++;
}

void 	ft_take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0 && should_continue(philo))
	{
		pthread_mutex_lock(philo->right_fork);
		ft_print(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		ft_print(philo, "has taken a fork");
		return ;
	}
	else if (should_continue(philo))
	{
		pthread_mutex_lock(philo->left_fork);
		ft_print(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		ft_print(philo, "has taken a fork");
		return ;
	}
}

static void ft_eat(t_philo *philo)
{
	if (philo->data->n_of_philos == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		ft_print(philo, "has taken a fork");
		usleep(philo->data->t_t_die * 1000);
		pthread_mutex_unlock(philo->left_fork);
		return;
	}
	ft_take_forks(philo);
	if (should_continue(philo))
	{
		ft_eat_helper(philo);
	}
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

int	check_stop_simulation(t_philo *philo)
{
	int	stop;

	pthread_mutex_lock(&philo->data->simulation_lock);
	stop = philo->data->stop_simulation;
	pthread_mutex_unlock(&philo->data->simulation_lock);
	return (stop);
}

void *routine(void *arg)
{
    t_philo *philo;
    long time_since_last_meal;

    philo = (t_philo *)arg;
    if (philo->id % 2 == 1)
        usleep(philo->data->t_t_eat * 500);
    while (should_continue(philo))
    {
        ft_eat(philo);
        if (should_continue(philo))
        {
            ft_print(philo, "is sleeping");
            usleep(philo->data->t_t_sleep * 1000);
        }
        if (should_continue(philo))
        {
            ft_print(philo, "is thinking");
            pthread_mutex_lock(&philo->data->simulation_lock);
            time_since_last_meal = get_time() - philo->last_meal;
            pthread_mutex_unlock(&philo->data->simulation_lock);
            if (philo->data->t_t_die - time_since_last_meal > 100)
                usleep(500);
        }
    }
    return (NULL);
}

