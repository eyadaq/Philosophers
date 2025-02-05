/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaqrabaw <eaqrabaw@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 06:48:43 by eaqrabaw          #+#    #+#             */
/*   Updated: 2025/02/05 12:05:56 by eaqrabaw         ###   ########.fr       */
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

int     ft_atoi(char *str)
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

int     ft_check_input(int argc, char *argv[])
{
    int     x;

    x = 1;
    if (!(argc == 5 || argc == 6))
    {
        write (2, "Invalid Arguments\n", 19);
        return (0);
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
    return (1);
}
