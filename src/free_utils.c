/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaqrabaw <eaqrabaw@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 09:46:43 by eaqrabaw          #+#    #+#             */
/*   Updated: 2025/05/10 00:38:23 by eaqrabaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_threads(t_philo **philo, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_join(philo[i]->thread, NULL);
		free(philo[i]);
		i++;
	}
	free(philo);
}

void	cleanup_all(t_philo **philo, t_data *data, int created)
{
	free_threads(philo, created);
	free(data->forks);
}
