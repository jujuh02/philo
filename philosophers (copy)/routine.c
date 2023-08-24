/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhaamid <juhaamid@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 10:21:46 by juhaamid          #+#    #+#             */
/*   Updated: 2023/08/24 12:31:40 by juhaamid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    eat(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->fork[philo->numphilo - 1]);
    status(philo, "has taken a fork", 1);
    pthread_mutex_lock(&philo->data->fork[philo->numphilo % philo->data->number_of_philosophers]);
    status(philo, "has taken a fork", 1);
    status(philo, "is eating,", 1);
    philo->data->last_eat[philo->num - 1] = get_time();
    myusleep(philo->data->time_to_eat);
    pthread_mutex_unlock(&philo->data->fork[philo->numphilo - 1]);
	pthread_mutex_unlock(&philo->data->fork[philo->numphilo % philo->data->number_of_philosophers]); 
}

void	sleep(t_philo *philo)
{
	status(philo, "is sleeping 😴", 1);
	myusleep(philo->data->time_to_sleep);
}

void	think(t_philo *philo)
{
	status(philo, "the philo is thinking", 1);
}

void    *is_dead(t_philo *philo)
{
    int i;
    i = 0;
    while (1)
    {
        i = 0;
        while(i < philo->data->number_of_philosophers)
        {
            if (philo[i].data->time_to_die <= get_time() - philo[i].data->last_eat[i])
            {
                if (philo[i].flag != 1)
                    status(&philo[i], died, 0);
                philo[i].data-> 1;
                break;
            }
            i++;
        }
        if (philo->data->death == 1)
            break;
    }
    return (NULL);
}
