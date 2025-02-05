/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaqrabaw <eaqrabaw@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 06:48:43 by eaqrabaw          #+#    #+#             */
/*   Updated: 2025/02/05 11:04:33 by eaqrabaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int     ft_isdigit(char c)
{
    if (c >= '0' && c <= '9')
        return (1);
    else
        return (0);
}

static int    ft_isnumber(char *str)
{
    while (*str == ' ')
        str++;
    if (*str == '+' || *str == '-')
        str++;
    while (ft_isdigit(*str))
        str++;
    return (*str == '\0');
}

static int     ft_atoi(char *str)
{
    int     number;
    
    number = 0;
    while (*str <= ' ' && *str)
        str++;
    if (*str == '+')
        str++;
    else if (*str == '-')
        return (0);
    while (ft_isdigit(*str))
    {
        number = (number * 10) + (*str - '0');
        str++;
    }
    return (number);
}

static int  ft_initialize(int argc, char *argv[], t_data *data)
{
    data->num_philo = ft_atoi(argv[1]);
    data->time_to_die = ft_atoi(argv[2]);
    data->time_to_eat = ft_atoi(argv[3]);
    data->time_to_sleep = ft_atoi(argv[4]);
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
    return (1);
}

int     ft_check_initialize(int argc, char *argv[], t_data *data)
{
    int     x;

    x = 1;
    if (!(argc == 5 || argc == 6))
    {
        write (2, "Invalid Arguments\n", 19);
        return (1);
    }
    while (x < argc)
    {
        if (!ft_isnumber(argv[x]))
        {
            write (2, "Invalid Arguments\n", 19);
            return (0);
        }
        x++;
    }
    if(!ft_initialize(argc, argv, data))
    {
        write (2, "Invalid Arguments\n", 19);
        return (0);
    }
    return (1);
}
