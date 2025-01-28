/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaqrabaw <eaqrabaw@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 08:01:36 by eaqrabaw          #+#    #+#             */
/*   Updated: 2025/01/27 09:04:23 by eaqrabaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/philosophers.h"
void *philosopher_routine(void *arg)
{
    t_philosopher *philo = (t_philosopher *)arg;
    
    while (/*......*/)
    {
        ft_eat(philo);
        ft_think(philo);
        ft_sleep(philo);
    }
    return (NULL);
}

void		ft_init_philosophers(t_data *data)
{

}
int main(int argc, char *argv[])
{
    t_data data;
    
    if (!ft_check_initialize(argc, argv, &data))
        return (1);
    ft_init_philosophers(&data);
    return (0);
}