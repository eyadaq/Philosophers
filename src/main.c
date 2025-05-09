/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaqrabaw <eaqrabaw@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 06:51:52 by eaqrabaw          #+#    #+#             */
/*   Updated: 2025/05/10 00:42:07 by eaqrabaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	allocate_memory(t_data *data, t_philo ***philos)
{
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_of_philos);
	if (!data->forks)
	{
		write(2, "Malloc failed for forks\n", 25);
		return (0);
	}
	*philos = malloc(sizeof(t_philo *) * data->n_of_philos);
	if (!*philos)
	{
		write(2, "Malloc failed for philosophers\n", 32);
		free(data->forks);
		return (0);
	}
	return (1);
}

int	create_monitor_thread(t_data *data, t_philo **philos)
{
	if (pthread_create(&data->monitor_thread, NULL, monitor, philos) != 0)
	{
		write(2, "Failed to create monitor thread\n", 33);
		return (0);
	}
	return (1);
}

int	run_simulation(t_data *data, t_philo **philos)
{
	if (!init_mutexes(data))
	{
		free(data->forks);
		free(philos);
		return (0);
	}
	if (!init_philos(data, philos))
	{
		free(data->forks);
		free(philos);
		return (0);
	}
	if (!create_monitor_thread(data, philos))
	{
		cleanup_all(philos, data, data->n_of_philos);
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	**philos;

	if (!check_initiate(&data, argc, argv))
		return (1);
	if (!allocate_memory(&data, &philos))
		return (1);
	if (!run_simulation(&data, philos))
		return (1);
	join_threads(&data, philos);
	free(data.forks);
	return (0);
}
