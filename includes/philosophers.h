/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaqrabaw <eaqrabaw@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 08:01:24 by eaqrabaw          #+#    #+#             */
/*   Updated: 2025/05/09 22:49:24 by eaqrabaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# define FT_INT_MAX 2147483647
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

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

/* input_validation.c */
int		input_validation(int argc, char **argv);
int		check_sign(char **str);
int		is_all_digit(char *str);
int		check_arg_digits(int argc, char **argv);
long	get_time(void);

/* initiate_input.c */
void	skip_spaces(char **str);
long	ft_atol(char *str);
int		init_data_values(t_data *data, int argc, char **argv);
int		init_simulation_state(t_data *data);
int		check_initiate(t_data *data, int argc, char **argv);

/* initiate_philos.c */
int		join_threads(t_data *data, t_philo **philo);
int		setup_philo(t_data *data, t_philo *philo, int philo_id);
int		fill_philo(t_data *data, t_philo **philo, int philo_id);
int		init_mutexes(t_data *data);
int		create_philo_thread(t_philo *philo);
int		create_philo_threads(t_data *data, t_philo **philo);
int		init_philos(t_data *data, t_philo **philo);

/* free_utils.c */
void	free_threads(t_philo **philo, int count);
void	destroy_forks(t_data *data, int count);
void	cleanup_all(t_philo **philo, t_data *data, int created);

/* monitor.c */
void	ft_stop(t_data *data);
int		check_philo_death(t_philo *philo);
void	print_death_message(t_philo *philo);
int		check_all_ate_enough(t_philo **philos, t_data *data);
int		monitor_philos(t_philo **philos, t_data *data);
void	*monitor(void *arg);

/* routine.c */
void	ft_print(t_philo *philo, char *str);
void	ft_eat(t_philo *philo);
int		check_stop_simulation(t_philo *philo);
int		should_continue(t_philo *philo);
void	*routine(void *arg);

#endif
