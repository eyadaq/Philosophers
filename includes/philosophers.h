/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaqrabaw <eaqrabaw@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 08:01:24 by eaqrabaw          #+#    #+#             */
/*   Updated: 2025/01/27 07:45:05 by eaqrabaw         ###   ########.fr       */
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

typedef struct s_philo
{
	int		n_philosophers;
	int		t_die;
	int		t_eat;
	int		t_sleep;
	int		n_eat;
	
}			t_philo;

int     	ft_atoi(char *str);
int     	ft_isdigit(char c);
int    		ft_isnumber(char *str);
int     	ft_check_arguments(int argc, char *argv[]);
void    	ft_initialize(t_philo *p, int argc, char *argv[]);
void        ft_eat(t_philo *ph);
void        ft_think(t_philo *ph);
void        ft_sleep(t_philo *ph);
#endif