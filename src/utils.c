/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaqrabaw <eaqrabaw@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 00:46:30 by eaqrabaw          #+#    #+#             */
/*   Updated: 2025/05/10 03:05:34 by eaqrabaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	setup_philo(t_data *data, t_philo *philo, int philo_id)
{
	philo->id = philo_id;
	philo->data = data;
	philo->n_of_meals_eaten = 0;
	philo->last_meal = data->start_time;
	philo->left_fork = &data->forks[philo_id];
	philo->right_fork = &data->forks[(philo_id + 1) % data->n_of_philos];
	return (1);
}

int	fill_philo(t_data *data, t_philo **philo, int philo_id)
{
	*philo = malloc(sizeof(t_philo));
	if (!*philo)
	{
		write(2, "Malloc failed for philosopher\n", 31);
		return (0);
	}
	if (!setup_philo(data, *philo, philo_id))
		return (0);
	return (1);
}

void	ft_stop(t_data *data)
{
	pthread_mutex_lock(&data->simulation_lock);
	data->stop_simulation = 1;
	pthread_mutex_unlock(&data->simulation_lock);
}

int	should_continue(t_philo *philo)
{
	if (check_stop_simulation(philo))
		return (0);
	if (philo->data->must_eat != -1
		&& philo->n_of_meals_eaten >= philo->data->must_eat)
		return (0);
	return (1);
}