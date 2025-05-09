/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaqrabaw <eaqrabaw@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 09:46:43 by eaqrabaw          #+#    #+#             */
/*   Updated: 2025/05/10 01:43:20 by eaqrabaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_threads(t_philo **philo, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_join(philo[i]->thread, NULL);
		free(philo[i]);
		i++;
	}
	free(philo);
}

void	destroy_mutexes(t_data *data)
{
	int		i;
    
	i = 0;
	while (i < data->n_of_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->simulation_lock);
}

void	cleanup_all(t_philo **philo, t_data *data, int created)
{
	free_threads(philo, created);
	destroy_mutexes(data);
	free(data->forks);
}

