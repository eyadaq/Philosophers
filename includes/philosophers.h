/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaqrabaw <eaqrabaw@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 08:01:24 by eaqrabaw          #+#    #+#             */
/*   Updated: 2025/02/05 10:27:05 by eaqrabaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# define FT_INT_MAX 2147483647
#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct  s_philosoher
{
	int		id;
}		t_philosopher;

typedef struct  s_data
{
	int         num_philo;
	int			time_to_die;
	int			num_must_eat;
	int			time_to_eat;
	int			time_to_sleep;
	t_philosopher	*philosophers;
}			t_data;

int     ft_check_initialize(int argc, char *argv[], t_data *data);

#endif