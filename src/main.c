/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaqrabaw <eaqrabaw@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 08:01:36 by eaqrabaw          #+#    #+#             */
/*   Updated: 2025/02/06 07:54:57 by eaqrabaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int     main(int argc, char *argv[])
{
    t_data  data;
    
    if (!ft_check_input(argc, argv))
        return (1);
    if (!ft_initialize(argc, argv, &data))
        return (1);
    monitor_philosophers(&data);
    ft_free(&data);
    return (0);
}