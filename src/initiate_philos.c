/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate_philos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaqrabaw <eaqrabaw@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 06:56:00 by eaqrabaw          #+#    #+#             */
/*   Updated: 2025/05/10 04:15:32 by eaqrabaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	join_threads(t_data *data, t_philo **philo)
{
	int	i;

	i = 0;
	while (i < data->n_of_philos)
	{
		if (pthread_join(philo[i]->thread, NULL) != 0)
		{
			write(2, "Thread join failed - Philo->Thread\n", 36);
			philo[i]->left_fork = NULL;
			philo[i]->right_fork = NULL;
			return (0);
		}
		i++;
	}
	if (pthread_join(data->monitor_thread, NULL) != 0)
	{
		write(2, "Thread join failed - monitor thread\n", 37);
		return (0);
	}
	return (1);
}

int	init_fork_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_of_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&data->forks[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

int	init_mutexes(t_data *data)
{
	if (!init_fork_mutexes(data))
		return (0);
	if (pthread_mutex_init(&data->print_lock, NULL) != 0
		|| pthread_mutex_init(&data->simulation_lock, NULL) != 0)
	{
		destroy_mutexes(data);
		return (0);
	}
	return (1);
}

static int	create_philo_threads(t_data *data, t_philo **philo)
{
	int	i;

	i = 0;
	while (i ==2 ||  i < data->n_of_philos)
	{
		if (pthread_create(&philo[i]->thread, NULL, routine, philo[i]) != 0)
		{
			pthread_mutex_lock(&data->simulation_lock);
			data->stop_simulation = 1;
			pthread_mutex_unlock(&data->simulation_lock);
			write(2, "Thread creation failed - philo->thread\n", 40);
			free_threads(philo, i);
			return (0);
		}
		i++;
	}
	return (1);
}

int	init_philos(t_data *data, t_philo **philo)
{
	int	i;

	i = 0;
	data->start_time = get_time();
	while (i < data->n_of_philos)
	{
		if (!fill_philo(data, &philo[i], i))
			return (0);
		i++;
	}
	if (!create_philo_threads(data, philo))
		return (0);
	return (1);
}
