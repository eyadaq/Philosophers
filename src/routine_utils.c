/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaqrabaw <eaqrabaw@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 07:57:45 by eaqrabaw          #+#    #+#             */
/*   Updated: 2025/02/06 09:44:30 by eaqrabaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void init_simulation_start_time(t_data *data)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    data->start_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

long get_time(t_data *data)
{
    struct timeval tv;
    long current_time;
    
    gettimeofday(&tv, NULL);
    current_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
    if (current_time < data->start_time)
    {
        printf("Error: current_time < start_time. Something went wrong.\n");
        return 0;
    }
    return (current_time - data->start_time);
}

void print_action(t_data *data, int id, char *action)
{
    long timestamp;

    pthread_mutex_lock(&data->write_lock);
    timestamp = get_time(data);
    data->philosophers[id - 1].last_meal_time = timestamp;
    if (!data->simulation_over)
        printf("%ld %d %s\n", timestamp, id, action);
    pthread_mutex_unlock(&data->write_lock);
}
