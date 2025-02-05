/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaqrabaw <eaqrabaw@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:37:06 by eaqrabaw          #+#    #+#             */
/*   Updated: 2025/02/05 12:03:32 by eaqrabaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*philosopher_routine(void *args)
{
	t_philosopher	*philo;
	struct timeval	tv;

	philo = (t_philosopher *)args;
	gettimeofday(&tv, NULL);
	philo->last_meal_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	printf("Philosopher %d has started their routine\n", philo->id);
	return (NULL);
}
