/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaqrabaw <eaqrabaw@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 06:48:43 by eaqrabaw          #+#    #+#             */
/*   Updated: 2025/01/27 08:24:15 by eaqrabaw         ###   ########.fr       */
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

static int    ft_initialize(t_data *p, char *argv[])
{
    p->n_philosophers = ft_atoi(argv[1]);
    p->t_die = ft_atoi(argv[2]);
    p->t_eat = ft_atoi(argv[3]);
    p->t_sleep = ft_atoi(argv[4]);
    p->n_eat = ft_atoi(argv[5]);
    p->forks = malloc(sizeof(t_fork) * p->n_philosophers);
    if (!p->forks)
    {
        write(2, "Malloc Failed\n", 15);  
        return (0);
    }
    p->philosophers = malloc(sizeof(t_philosopher) * p->n_philosophers);
    if (!p->philosophers)
    {
        write(2, "Malloc Failed\n", 15);
        free(p->forks);
        return (0);   
    }
    return (1);   
}

int     ft_check_initialize(int argc, char *argv[], t_data *data)
{
    int     x;

    x = 1;
    if (argc != 6)
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
    if (!ft_initialize(data, argv))
        return (0);
    return (1);
}