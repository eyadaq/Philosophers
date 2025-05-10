/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaqrabaw <eaqrabaw@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 09:46:43 by eaqrabaw          #+#    #+#             */
/*   Updated: 2025/05/10 02:59:32 by eaqrabaw         ###   ########.fr       */
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