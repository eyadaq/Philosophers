/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaqrabaw <eaqrabaw@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 11:17:27 by eaqrabaw          #+#    #+#             */
/*   Updated: 2025/05/10 01:07:44 by eaqrabaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_philo_death(t_philo *philo)
{
	long	time_since_meal;

	pthread_mutex_lock(&philo->data->simulation_lock);
	time_since_meal = get_time() - philo->last_meal;
	pthread_mutex_unlock(&philo->data->simulation_lock);
	if (time_since_meal > philo->data->t_t_die)
		return (1);
	return (0);
}

int	check_all_ate_enough(t_philo **philos, t_data *data)
{
	int	i;
	int	all_ate;

	if (data->must_eat == -1)
		return (0);
	all_ate = 1;
	i = 0;
	while (i < data->n_of_philos)
	{
		if (philos[i]->n_of_meals_eaten < data->must_eat)
		{
			all_ate = 0;
			break ;
		}
		i++;
	}
	return (all_ate);
}

void	dead_action(t_philo **philos, t_data *data, int i,
		long *time_since_meal)
{
	pthread_mutex_lock(&data->print_lock);
	pthread_mutex_lock(&data->simulation_lock);
	*time_since_meal = get_time() - philos[i]->last_meal;
	if ((*time_since_meal > data->t_t_die) && !data->stop_simulation)
	{
		data->stop_simulation = 1;
		printf("%ld %d died\n", get_time() - data->start_time, philos[i]->id
			+ 1);
	}
	pthread_mutex_unlock(&data->simulation_lock);
	pthread_mutex_unlock(&data->print_lock);
}

int	monitor_philos(t_philo **philos, t_data *data)
{
	int		i;
	int		is_dead;
	long	time_since_meal;

	i = 0;
	is_dead = 0;
	while (i < data->n_of_philos)
	{
		pthread_mutex_lock(&data->simulation_lock);
		time_since_meal = get_time() - philos[i]->last_meal;
		if (time_since_meal > data->t_t_die)
			is_dead = 1;
		pthread_mutex_unlock(&data->simulation_lock);
		if (is_dead)
		{
			dead_action(philos, data, i, &time_since_meal);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_philo	**philos;
	t_data	*data;

	philos = (t_philo **)arg;
	data = philos[0]->data;
	usleep(1000);
	while (1)
	{
		if (monitor_philos(philos, data))
			return (NULL);
		if (check_all_ate_enough(philos, data))
		{
			ft_stop(data);
			return (NULL);
		}
		usleep(500);
	}
}
