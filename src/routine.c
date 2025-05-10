/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaqrabaw <eaqrabaw@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 07:26:42 by eaqrabaw          #+#    #+#             */
/*   Updated: 2025/05/10 03:30:46 by eaqrabaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_sleep(t_philo *philo)
{
	long	start_time;

	if (should_continue(philo))
	{
		ft_print(philo, "is sleeping");
		start_time = get_time();
		while (get_time() - start_time < philo->data->t_t_sleep)
		{
			if (check_stop_simulation(philo))
				return ;
			usleep(1000);
		}
	}
}

void	ft_think(t_philo *philo)
{
	long	time_since_last_meal;

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

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 1)
		usleep(500);
	while (should_continue(philo))
	{
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (NULL);
}
