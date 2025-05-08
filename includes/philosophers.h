/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaqrabaw <eaqrabaw@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 08:01:24 by eaqrabaw          #+#    #+#             */
/*   Updated: 2025/05/08 06:54:30 by eaqrabaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# define FT_INT_MAX 2147483647
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

typedef struct s_data
{
	int			n_of_meals_eaten;
	int			t_t_die;
	int			t_t_sleep;
	int			t_t_eat;
	int			n_of_philos;
}					t_data;

typedef struct s_philo
{
	int			id;
	int			last_meal;
	int			n_of_meals_eaten;
	pthread_t	thread;
	t_data		*data;	
	pthread_mutex_t	left_fork;
	pthread_mutex_t	right_fork;
}					t_philo;

int					input_validation(int argc, char **argv);
void 				skip_spaces(char **str);
int					check_initiate(t_data *data, int argc, char **argv);

#endif