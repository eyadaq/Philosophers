/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaqrabaw <eaqrabaw@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:46:05 by eaqrabaw          #+#    #+#             */
/*   Updated: 2025/02/06 09:20:04 by eaqrabaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	ft_free(t_data *data)
{
	if (data->forks)
		free(data->forks);
	if (data->philosophers)
		free(data->philosophers);
}

static int ft_join_threads(t_data *data)
{
	int 	i;

	i = 0;
	while(i < data->num_philo)
	{
    	if (pthread_join(data->philosophers[i].thread, NULL) != 0)
    	{
        	printf("Error: Failed to join thread\n");
			ft_free(data);
        	return (0);
		}
		i++;
    }
	return (1);
}

static int ft_init_threads(t_data *data)
{
	int 	i;

	i = 0;
	while (i < data->num_philo)
	{
		data->philosophers[i].id = i + 1;
		data->philosophers[i].meals_eaten = 0;
		data->philosophers[i].last_meal_time = 0;
		data->philosophers[i].left_fork = i;
		data->philosophers[i].right_fork = (i + 1) % data->num_philo;
		data->philosophers[i].data = data;
		if (pthread_create(&data->philosophers[i].thread, NULL, philosopher_routine, &data->philosophers[i]) != 0)
		{
			write(2, "Thread Creation Failed\n", 23);
			ft_free(data);
			return (0);
		};
		i++;
	}
	if (!ft_join_threads(data))
		return (0);
	return (1);
}

static int ft_init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			write(2, "Mutex Creation Failed\n", 22);
			ft_free(data);
			return (0);
		}
		i++;
	}
	if (pthread_mutex_init(&data->stop_lock, NULL) != 0 || pthread_mutex_init(&data->write_lock, NULL) != 0)
	{
		write(2, "Mutex Creation Failed\n", 22);
		ft_free(data);
		return (0);
	}
	return (1);
}

int	ft_initialize(int argc, char *argv[], t_data *data)
{
    data->num_philo = ft_atoi(argv[1]);
    data->time_to_die = ft_atoi(argv[2]);
    data->time_to_eat = ft_atoi(argv[3]);
    data->time_to_sleep = ft_atoi(argv[4]);
	data->simulation_over = 0;
    if (argc == 6)
        data->num_must_eat = ft_atoi(argv[5]);
    else
        data->num_must_eat = -1;
    data->philosophers = malloc(data->num_philo * sizeof(t_philosopher));
	if (!data->philosophers)
		return (0);
    data->forks = malloc(data->num_philo * sizeof(pthread_mutex_t));
    if (!data->forks)
    {
        ft_free(data);
        return (0);
    }
	if (!ft_init_mutexes(data) || !ft_init_threads(data))
		return (0);
	return (1);
}
