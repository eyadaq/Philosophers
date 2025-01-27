/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaqrabaw <eaqrabaw@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 08:01:36 by eaqrabaw          #+#    #+#             */
/*   Updated: 2025/01/27 08:57:45 by eaqrabaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/philosophers.h"
void *philosopher_routine(void *arg)
{
    t_philosopher *philo = (t_philosopher *)arg;
    
    while (/*......*/)
    {
        ft_eat(philo);
        ft_think(philo);
        ft_sleep(philo);
    }
    return (NULL);
}


void		ft_init_philosophers(t_data *data)
{
    int i;

    i = 0;
    while (i < data->n_philosophers)
    {
        data->philosophers[i].id = i + 1;
        data->forks[i].id = i + 1;
        pthread_create(&data->philosophers[i].thread, NULL, philosopher_routine, &data->philosophers[i]);
        i++;
    }
    i = 0;
    while (i < data->n_philosophers)
    {
        pthread_join(data->philosophers[i].thread, NULL);
        i++;
    }
    
}

int main(int argc, char *argv[])
{
    t_data data;
    
    if (!ft_check_initialize(argc, argv, &data))
        return (1);
    ft_init_philosophers(&data);
    return (0);
}