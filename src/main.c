/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaqrabaw <eaqrabaw@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 06:51:52 by eaqrabaw          #+#    #+#             */
/*   Updated: 2025/05/08 11:43:32 by eaqrabaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		main(int argc, char **argv)
{
	t_data			data;
	t_philo 		**philos;
	pthread_t		monitor_thread;

	if (!check_initiate(&data, argc, argv))
		return (1);
	philos = malloc(sizeof(t_philo *) * data.n_of_philos);
	if (!philos)
	{
		write(2, "Malloc failed\n", 14);
		return (1);
	}
	if (!init_philos(&data, philos))
		return (1);
	if (pthread_create(&monitor_thread, NULL, monitor, philos))
	{
		write(2, "Failed to create monitor\n", 26);
		free_threads(philos, data.n_of_philos);
		return (1);
	}
	pthread_join(monitor_thread, NULL);
	free_threads(philos, data.n_of_philos);
	destroy_mutexes(&data, data.n_of_philos);
	return (0);	
}
