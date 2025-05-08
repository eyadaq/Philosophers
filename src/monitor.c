/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaqrabaw <eaqrabaw@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 11:17:27 by eaqrabaw          #+#    #+#             */
/*   Updated: 2025/05/08 11:35:49 by eaqrabaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_stop(t_data *data)
{
    pthread_mutex_lock(&data->simulation_lock);
	data->stop_simulation = 1;
	pthread_mutex_unlock(&data->simulation_lock);
}

void 	*monitor(void *arg)
{
	t_philo	**philos;
	t_data	*data;
    int     i;

	philos = (t_philo **)arg;
	data = philos[0]->data;
	while (1)
	{
        i = 0;
		while (i < data->n_of_philos)
		{
			pthread_mutex_lock(&data->print_lock);
			if (get_time() - philos[i]->last_meal > data->t_t_die)
			{
				printf("%5ld %5d died\n", get_time() - data->start_time, philos[i]->id + 1);
				pthread_mutex_unlock(&data->print_lock);
				ft_stop(data);
				return (NULL);
			}
			pthread_mutex_unlock(&data->print_lock);
            i++;
		}
		usleep(1000);
	}
}
