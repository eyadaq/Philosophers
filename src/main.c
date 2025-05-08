/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaqrabaw <eaqrabaw@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 06:51:52 by eaqrabaw          #+#    #+#             */
/*   Updated: 2025/05/08 10:20:34 by eaqrabaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		main(int argc, char **argv)
{
	t_data		data;
	t_philo 		**philos;

	if (!check_initiate(&data, argc, argv))
		return (1);
	philos = malloc(sizeof(t_philo *) * data.n_of_philos);
	if (!philos)
	{
		write(2, "Malloc failed\n", 14);
		return (1);
	}
	if (!init_philos(&data, philos))
		return (1);
	return (0);	
}