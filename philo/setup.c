/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhaamid <juhaamid@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 11:24:44 by juhaamid          #+#    #+#             */
/*   Updated: 2023/08/29 17:10:14 by juhaamid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->number_of_philosophers == 1)
	{
		if (ft_handle_lonely_philo(philo) != 0)
			return (0);
	}
	else
	{
		pthread_mutex_lock(&philo->data->lock);
		while (philo->data->death == 0)
		{
			pthread_mutex_unlock(&philo->data->lock);
			usleep(100);
			if (take_forks(philo, philo->numphilo) && sleeeep(philo) != 1
				&& think(philo))
				return (0);
			pthread_mutex_lock(&philo->data->lock);
		}
		pthread_mutex_unlock(&philo->data->lock);
	}
	return (0);
}

int	ft_init_mutexes(t_data *table)
{
	int	i;

	i = -1;
	if (pthread_mutex_init(&table->print, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&table->lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&table->pop_mutex, NULL) != 0)
		return (1);
	table->fork = malloc(sizeof(pthread_mutex_t) \
		* table->number_of_philosophers);
	table->sign = malloc(sizeof(int) * table->number_of_philosophers);
	table->avail = malloc(sizeof(int) * table->number_of_philosophers);
	if (!table->fork ||!table->avail || !table->sign)
		return (1);
	while (++i < table->number_of_philosophers)
	{
		if (pthread_mutex_init(&table->fork[i], NULL) != 0)
			return (1);
		table->sign[i] = -1;
		table->avail[i] = 1;
	}
	return (0);
}

int	initphilo(t_data *table)
{
	int	i;

	i = -1;
	table->philo = malloc(sizeof(t_philo) * table->number_of_philosophers);
	if (table->philo == NULL)
		return (1);
	while (++i < table->number_of_philosophers)
	{
		table->philo[i].numphilo = i;
		table->philo[i].data = table;
		table->philo[i].meal = 0;
		table->philo[i].timeoflastmeal = 0;
	}
	return (0);
}

int	settable(char **av, t_data *table)
{
	table->number_of_philosophers = ft_atoi(av[1]);
	if (table->number_of_philosophers <= 0 || 
		table->number_of_philosophers >= 201)
		return (1);
	table->time_to_die = ft_atoi(av[2]);
	if (table->time_to_die <= 0 || table->time_to_die <= 61)
		return (1);
	table->time_to_eat = ft_atoi(av[3]);
	if (table->time_to_eat <= 0 || table->time_to_eat <= 61)
		return (1);
	table->time_to_sleep = ft_atoi(av[4]);
	if (table->time_to_sleep <= 0 || table->time_to_sleep <= 61)
		return (1);
	if (av[5])
	{
		table->num_of_tepme = ft_atoi(av[5]);
		if (table->num_of_tepme <= 0)
			return (1);
	}
	else
		table->num_of_tepme = -1;
	table->death = 0;
	return (0);
}

int	start(t_data *table)
{
	pthread_t	*pthread;
	int			i;

	pthread = malloc(sizeof(pthread_t) * table->number_of_philosophers);
	if (pthread == NULL)
		return (1);
	i = -1;
	table->time = get_time();
	while (++i < table->number_of_philosophers)
	{
		if (pthread_create(&pthread[i], NULL,
				&routine, &table->philo[i]) != 0)
		{
			free(pthread);
			return (1);
		}
	}
	ft_loop_main_thread(table);
	if (ft_unlock_and_join(table, pthread) != 0)
		return (1);
	return (0);
}
