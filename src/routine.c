/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaqrabaw <eaqrabaw@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 07:26:42 by eaqrabaw          #+#    #+#             */
/*   Updated: 2025/05/10 02:00:15 by eaqrabaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_print(t_philo *philo, char *str)
{
	if (should_continue(philo))
	{
		pthread_mutex_lock(&philo->data->print_lock);
		printf("%6.0ld %3.0d %s\n", (long)(get_time()
				- philo->data->start_time), philo->id + 1, str);
		pthread_mutex_unlock(&philo->data->print_lock);
	}
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

void	ft_eat(t_philo *philo)
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
		ft_print(philo, "is eating");
		pthread_mutex_lock(&philo->data->simulation_lock);
        philo->last_meal = get_time();
        pthread_mutex_unlock(&philo->data->simulation_lock);
        usleep(philo->data->t_t_eat * 1000);
        philo->n_of_meals_eaten++;
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

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
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
			usleep(10);
		}
	}
	return (NULL);
}
