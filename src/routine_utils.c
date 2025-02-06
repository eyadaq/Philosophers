/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaqrabaw <eaqrabaw@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 07:57:45 by eaqrabaw          #+#    #+#             */
/*   Updated: 2025/02/06 09:16:52 by eaqrabaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void init_simulation_start_time(t_data *data)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    // Store time in milliseconds
    data->start_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}



long get_time(t_data *data)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    long current_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);

    // Ensure the elapsed time is not negative (it shouldn't be unless there's a system clock issue)
    if (current_time < data->start_time)
    {
        // This check shouldn't typically happen. If it does, handle accordingly (reset start_time, etc.)
        printf("Error: current_time < start_time. Something went wrong.\n");
        return 0;
    }
    printf("Start time: %ld ms\n", data->start_time);
    printf("Current time: %ld ms\n", current_time);

    return (current_time - data->start_time);
}



void print_action(t_data *data, int id, char *action)
{
    long timestamp;

    pthread_mutex_lock(&data->write_lock);
    timestamp = get_time(data);
    if (!data->simulation_over)
        printf("%ld %d %s\n", timestamp, id, action);
    pthread_mutex_unlock(&data->write_lock);
}
