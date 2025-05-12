/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaqrabaw <eaqrabaw@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 03:12:07 by eaqrabaw          #+#    #+#             */
/*   Updated: 2025/05/12 18:10:28 by eaqrabaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_eat_process(t_philo *philo, int *died_while_eating,
		long start_eating_time)
{
	long	current_time;
	long	time_since_last_meal;

	if (check_stop_simulation(philo))
		return (0);
	current_time = get_time();
	if (current_time - start_eating_time >= philo->data->t_t_eat)
		return (0);
	pthread_mutex_lock(&philo->data->simulation_lock);
	time_since_last_meal = current_time - philo->last_meal;
	if (time_since_last_meal >= philo->data->t_t_die
		&& !philo->data->stop_simulation)
	{
		philo->data->stop_simulation = 1;
		pthread_mutex_unlock(&philo->data->simulation_lock);
		pthread_mutex_lock(&philo->data->print_lock);
		printf("%6.0ld %3.0d has died\n", current_time
			- philo->data->start_time, philo->id + 1);
		pthread_mutex_unlock(&philo->data->print_lock);
		*died_while_eating = 1;
		return (0);
	}
	pthread_mutex_unlock(&philo->data->simulation_lock);
	usleep(100);
	return (1);
}

static int	ft_eat_helper(t_philo *philo)
{
	long	start_eating_time;
	int		died_while_eating;
	int		flag;

	died_while_eating = 0;
	flag = 1;
	pthread_mutex_lock(&philo->data->simulation_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->data->simulation_lock);
	ft_print(philo, "is eating");
	start_eating_time = get_time();
	while (flag)
		flag = ft_eat_process(philo, &died_while_eating, start_eating_time);
	if (should_continue(philo) && !died_while_eating)
	{
		pthread_mutex_lock(&philo->data->simulation_lock);
		philo->n_of_meals_eaten++;
		pthread_mutex_unlock(&philo->data->simulation_lock);
	}
	return (died_while_eating);
}

void	ft_take_forks(t_philo *philo)
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
		return ;
	}
	ft_take_forks(philo);
	if (should_continue(philo))
		ft_eat_helper(philo);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
