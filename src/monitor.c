/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaqrabaw <eaqrabaw@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 11:17:27 by eaqrabaw          #+#    #+#             */
/*   Updated: 2025/05/09 23:42:28 by eaqrabaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_stop(t_data *data)
{
	pthread_mutex_lock(&data->simulation_lock);
	data->stop_simulation = 1;
	pthread_mutex_unlock(&data->simulation_lock);
}

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

void print_death_message(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->print_lock);
    printf("%ld %d died\n", get_time() - philo->data->start_time, 
           philo->id + 1);
    pthread_mutex_unlock(&philo->data->print_lock);
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
			break;
		}
		i++;
	}
	return (all_ate);
}

void *monitor(void *arg)
{
    t_philo **philos;
    t_data *data;

    philos = (t_philo **)arg;
    data = philos[0]->data;
    
    // Give philos time to initialize
    usleep(1000);
    
    while (1)
    {
        // Check for death first
        if (monitor_philos(philos, data))
            return (NULL);
            
        // Then check if all have eaten enough
        if (check_all_ate_enough(philos, data))
        {
            ft_stop(data);
            return (NULL);
        }
        
        // Sleep for a shorter period for more responsive death detection
        usleep(500);
    }
}


int monitor_philos(t_philo **philos, t_data *data)
{
    int i;
    
    i = 0;
    while (i < data->n_of_philos)
    {
        long time_since_meal;
        
        pthread_mutex_lock(&data->simulation_lock);
        time_since_meal = get_time() - philos[i]->last_meal;
        int is_dead = time_since_meal > data->t_t_die;
        pthread_mutex_unlock(&data->simulation_lock);
        
        if (is_dead)
        {
            // Lock both print and simulation mutexes to prevent race conditions
            pthread_mutex_lock(&data->print_lock);
            pthread_mutex_lock(&data->simulation_lock);
            
            // Double-check death condition after acquiring locks
            time_since_meal = get_time() - philos[i]->last_meal;
            if (time_since_meal > data->t_t_die && !data->stop_simulation)
            {
                // Set stop flag before printing
                data->stop_simulation = 1;
                printf("%ld %d died\n", get_time() - data->start_time, 
                       philos[i]->id + 1);
            }
            
            pthread_mutex_unlock(&data->simulation_lock);
            pthread_mutex_unlock(&data->print_lock);
            return (1);
        }
        i++;
    }
    return (0);
}

