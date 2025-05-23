/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaqrabaw <eaqrabaw@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 11:17:27 by eaqrabaw          #+#    #+#             */
/*   Updated: 2025/05/12 18:11:24 by eaqrabaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_all_ate_enough(t_philo **philos, t_data *data)
{
	int		i;
	int		all_ate;
	int		meals;

	all_ate = 1;
	if (data->must_eat == -1)
		return (0);
	i = 0;
	while (i < data->n_of_philos)
	{
		pthread_mutex_lock(&(data->simulation_lock));
		meals = philos[i]->n_of_meals_eaten;
		pthread_mutex_unlock(&(data->simulation_lock));
		if (meals < data->must_eat)
		{
			all_ate = 0;
			break ;
		}
		i++;
	}
	return (all_ate);
}

int	monitor_philos(t_philo **philos, t_data *data)
{
	int		i;
	long	current_time;
	long	time_since_meal;

	i = 0;
	current_time = get_time();
	while (i < data->n_of_philos)
	{
		pthread_mutex_lock(&data->print_lock);
		pthread_mutex_lock(&data->simulation_lock);
		time_since_meal = current_time - philos[i]->last_meal;
		if (time_since_meal >= data->t_t_die)
		{
			data->stop_simulation = 1;
			printf("%6.0ld %3.0d has died\n", current_time - data->start_time,
				philos[i]->id + 1);
			pthread_mutex_unlock(&data->simulation_lock);
			pthread_mutex_unlock(&data->print_lock);
			return (1);
		}
		pthread_mutex_unlock(&data->simulation_lock);
		pthread_mutex_unlock(&data->print_lock);
		i++;
	}
	return (0);
}

int	ft_monitor_helper(t_data *data, t_philo **philos, int sleep_time)
{
	pthread_mutex_lock(&data->simulation_lock);
	if (data->stop_simulation)
	{
		pthread_mutex_unlock(&data->simulation_lock);
		return (0);
	}
	pthread_mutex_unlock(&data->simulation_lock);
	if (monitor_philos(philos, data))
		return (0);
	if (check_all_ate_enough(philos, data))
	{
		ft_stop(data);
		return (0);
	}
	usleep(sleep_time);
	return (1);
}

void	*monitor(void *arg)
{
	t_philo	**philos;
	t_data	*data;
	int		sleep_time;
	int		flag;

	flag = 1;
	philos = (t_philo **)arg;
	data = philos[0]->data;
	if (data->t_t_die < 10)
		sleep_time = 100;
	else
		sleep_time = 500;
	while (flag)
		flag = ft_monitor_helper(data, philos, sleep_time);
	return (NULL);
}
