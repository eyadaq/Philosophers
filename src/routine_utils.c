/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaqrabaw <eaqrabaw@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 07:57:45 by eaqrabaw          #+#    #+#             */
/*   Updated: 2025/02/06 08:16:40 by eaqrabaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

long 	get_time(void)
{
    struct timeval tv;
	
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000); // Convert to milliseconds
}

void print_action(t_data *data, int id, char *action)
{
    long timestamp;

    pthread_mutex_lock(&data->write_lock);
    timestamp = get_time() - data->start_time;
    if (!data->simulation_over)
        printf("%ld %d %s\n", timestamp, id, action);
    pthread_mutex_unlock(&data->write_lock);
}
