/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaqrabaw <eaqrabaw@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:30:58 by eaqrabaw          #+#    #+#             */
/*   Updated: 2025/05/10 03:02:35 by eaqrabaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000));
}

static int	is_all_digit(char *str)
{
	skip_spaces(&str);
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!(*str >= '0' && *str <= '9'))
			return (0);
		str++;
	}
	return (1);
}

static int	check_arg_digits(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!is_all_digit(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

int	input_validation(int argc, char **argv)
{
	if (argc != 6 && argc != 5)
		return (0);
	if (!check_arg_digits(argc, argv))
		return (0);
	return (1);
}
