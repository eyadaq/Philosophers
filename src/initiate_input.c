/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaqrabaw <eaqrabaw@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:53:43 by eaqrabaw          #+#    #+#             */
/*   Updated: 2025/05/09 05:14:44 by eaqrabaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	skip_spaces(char **str)
{
	while (**str == ' ' || **str == '\t' || **str == '\n' 
			|| **str == '\v' || **str == '\f' || **str == '\r')
		(*str)++;
}

long	ft_atol(char *str)
{
	long	i;
	int		sign;

	i = 0;
	sign = 1;
	skip_spaces(&str);
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
		i = i * 10 + (*str++ - '0');
	if (i > FT_INT_MAX || i < 0)
		return (-1);
	return (i * sign);
}

int		initiate_input(int argc, char **argv, t_data *data)
{
	data->n_of_philos = ft_atol(argv[1]);
	if(data->n_of_philos <= 0)
		return (0);
	data->t_t_die = ft_atol(argv[2]);
	if(data->t_t_die <= 0)
		return (0);
	data->t_t_eat = ft_atol(argv[3]);
	if(data->t_t_eat <= 0)
		return (0);
	data->t_t_sleep = ft_atol(argv[4]);
	if(data->t_t_sleep <= 0)
		return (0);
	if (argc == 6)
	{
		data->must_eat = ft_atol(argv[5]);
		if (data->must_eat < 0)
			return (0);
	}
	else 
		data->must_eat = -1;
	data->all_ate_enough = 0;
	data->start_time = 0;
	data->stop_simulation = 0;
	return (1);
}

int		check_initiate(t_data *data, int argc, char **argv)
{
	if (!input_validation(argc, argv))
		return (0);
	if (!initiate_input(argc, argv, data))
		return (0);
	return (1);
}