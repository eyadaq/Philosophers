/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaqrabaw <eaqrabaw@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 08:01:24 by eaqrabaw          #+#    #+#             */
/*   Updated: 2025/02/06 09:02:29 by eaqrabaw         ###   ########.fr       */
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
	pthread_t    thread;
	int			left_fork;
	int			right_fork;
	long		last_meal_time;
	int			meals_eaten;
	struct s_data		*data;
}		t_philosopher;

typedef struct  s_data
{
	int         num_philo;
	int			time_to_die;
	int			num_must_eat;
	int			time_to_eat;
	int			time_to_sleep;
	t_philosopher	*philosophers;
	int			simulation_over;
	long 		start_time;
	pthread_mutex_t *forks;
	pthread_mutex_t stop_lock;
	pthread_mutex_t write_lock;
}			t_data;

int     ft_check_input(int argc, char *argv[]);
void    ft_free(t_data *data);
int  	ft_initialize(int argc, char *argv[], t_data *data);
void	*philosopher_routine(void *args);
int     ft_atoi(char *str);
void 	monitor_philosophers(t_data *data);
long 	get_time(t_data *data);
void 	print_action(t_data *data, int id, char *action);
void	init_simulation_start_time(t_data *data);
#endif