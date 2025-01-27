/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaqrabaw <eaqrabaw@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 08:01:36 by eaqrabaw          #+#    #+#             */
/*   Updated: 2025/01/27 07:24:44 by eaqrabaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/philosophers.h"



int main(int argc, char *argv[])
{
    t_philo philos;
    
    if (!ft_check_arguments(argc, argv))
        return (1);
    ft_initialize(&philos, argc, argv);
    return (0);
}