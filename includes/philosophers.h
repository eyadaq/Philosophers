/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaqrabaw <eaqrabaw@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 08:01:24 by eaqrabaw          #+#    #+#             */
/*   Updated: 2025/01/27 08:57:13 by eaqrabaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct  s_fork
{
	int		id;
}			t_fork;

typedef struct  s_philosopher
{
	int		id;
	t_fork	left;
	t_fork	right;
	pthread_t thread;
}			t_philosopher;

typedef struct s_data
{
	int		n_philosophers;
	int		t_die;
	int		t_eat;
	int		t_sleep;
	int		n_eat;
	t_fork	*forks;
	t_philosopher	*philosophers;
}			t_data;

int     	ft_check_initialize(int argc, char *argv[], t_data *data);
void        ft_eat(t_data *ph);
void        ft_think(t_data *ph);
void        ft_sleep(t_data *ph);
void 		*philosopher_routine(void *arg);
void		ft_init_philosophers(t_data *data);
#endif