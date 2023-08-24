/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhaamid <juhaamid@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 11:24:44 by juhaamid          #+#    #+#             */
/*   Updated: 2023/08/24 12:32:22 by juhaamid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *routine(void *arg)
{
    t_philo *philo;
    int food;
    
    philo = (t_philo *)arg;
    food = 0;
    if (!(philo->numphilo % 2))
        usleep(100);
    while (1)
    {
        eat(philo);
        food++;
        if (philo->data->number_of_times_each_philosopher_must_eat != 1)
        {
            if (food >= philo->data->number_of_times_each_philosopher_must_eat)
            {
                philo->flag = 1;
                break ;
            }
        }
        sleep(philo);
        think(philo);
    }
    return (NULL);
}

int    initphilo(t_data *table)
{
    int i;
    
    i = -1;
    table->philo = malloc(sizeof(t_philo) * table->number_of_philosophers);
    table->fork = malloc(sizeof(pthread_mutex_t) * table->number_of_philosophers);
    table->last_eat = malloc(sizeof(long long) * table->number_of_philosophers);
    
    if (!table->philo || !table->fork || !table->last_eat)
        return (NULL);
    while(++i < table->number_of_philosophers)
    {
        pthread_mutex_init(&table->fork[i], NULL);
        table->philo[i].numphilo = i + 1;
        table->philo[i].data = table;
        table->death = 0;
        table->philo[i].flag = 0;
    }
    return(0);
}

t_data *settable(char **av)
{
    t_data *table;
    
    table = malloc(sizeof(t_data));
    if (!table)
        return (NULL);
    table->number_of_philosophers = ft_atoi(av[1]);
    table->time_to_die = ft_atoi(av[2]);
    table->time_to_eat = ft_atoi(av[3]);
    table->time_to_sleep = ft_atoi(av[4]);
    if (av[5])
        table->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
    else
        table->number_of_times_each_philosopher_must_eat = -1;
    return (table);
}

void    *start(t_data *table)
{
    int i;
    
    i = -1;
    table->time = get_time();
    table->death = 0;
    pthread_mutex_init(&table->lock, NULL);
    while (++i < table->number_of_philosophers);
    {
        table->last_eat[i] = get_time;
        pthread_create(&table->philo[i].ph, NULL, &routine, &table->philo[i]);
    }
    is_dead(table->philo);
    i = 0;
    while (i < data->number_of_philosophers && (!table->death))
    {
        pthread_join(table->philo[i].ph, NULL);
        i++;
    }
    return (0);
}