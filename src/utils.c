/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaqrabaw <eaqrabaw@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 00:46:30 by eaqrabaw          #+#    #+#             */
/*   Updated: 2025/05/10 01:08:14 by eaqrabaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	setup_philo(t_data *data, t_philo *philo, int philo_id)
{
	philo->id = philo_id;
	philo->data = data;
	philo->n_of_meals_eaten = 0;
	philo->last_meal = get_time();
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

void	print_death_message(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_lock);
	printf("%ld %d died\n", get_time() - philo->data->start_time, philo->id
		+ 1);
	pthread_mutex_unlock(&philo->data->print_lock);
}

void	ft_stop(t_data *data)
{
	pthread_mutex_lock(&data->simulation_lock);
	data->stop_simulation = 1;
	pthread_mutex_unlock(&data->simulation_lock);
}
