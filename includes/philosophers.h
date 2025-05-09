/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaqrabaw <eaqrabaw@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 08:01:24 by eaqrabaw          #+#    #+#             */
/*   Updated: 2025/05/09 05:01:39 by eaqrabaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# define FT_INT_MAX 2147483647
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct s_data
{
	int					n_of_philos;
	int					t_t_die;
	int					t_t_eat;
	int					t_t_sleep;
	int					must_eat;
	int					all_ate_enough;
	long				start_time;
	int					stop_simulation;
	pthread_mutex_t		simulation_lock;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_lock;
	pthread_t			monitor_thread;
}					t_data;

typedef struct s_philo
{
	int				id;
	long			last_meal;
	int				n_of_meals_eaten;
	pthread_t		thread;
	t_data			*data;	
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}					t_philo;


int					input_validation(int argc, char **argv);
void 				skip_spaces(char **str);
int					check_initiate(t_data *data, int argc, char **argv);
void    			*routine(void *arg);
void				free_threads(t_philo **philo, int count);
int					init_philos(t_data *data, t_philo **philo);
int     			init_mutexes(t_data *data);
void    			free_threads(t_philo **philo, int count);
void    			destroy_forks(t_data *data, int count);
void 				cleanup_all(t_philo **philo, t_data *data, int created);
void 				*monitor(void *arg);
long				get_time(void);
#endif