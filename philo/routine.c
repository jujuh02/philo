/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhaamid <juhaamid@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 14:06:33 by juhaamid          #+#    #+#             */
/*   Updated: 2023/08/29 15:41:37 by juhaamid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_loop_main_thread(t_data *table)
{
	pthread_mutex_lock(&table->pop_mutex);
	while (table->death == 0)
	{
		pthread_mutex_unlock(&table->pop_mutex);
		if (ft_routine_is_finished(table) == 1)
			return (0);
		if (is_dead(table) == 1)
			return (1);
		pthread_mutex_lock(&table->pop_mutex);
	}
	pthread_mutex_unlock(&table->pop_mutex);
	return (0);
}

int	ft_handle_lonely_philo(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (ft_print_state_change(philo, GRAB_FORK) != 0)
		return (1);
	if (myusleep(data->time_to_die, philo) != 0)
		return (1);
	return (0);
}

int	ft_unlock_and_join(t_data *table, pthread_t *pthread)
{
	int	i;

	i = -1;
	while (++i < table->number_of_philosophers)
	{
		if (pthread_join(pthread[i], NULL) != 0)
		{
			free(pthread);
			return (1);
		}
	}
	free(pthread);
	return (0);
}

int	sleeeep(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock);
	if (philo->data->death != 0)
	{
		pthread_mutex_unlock(&philo->data->lock);
	}
	else
		pthread_mutex_unlock(&philo->data->lock);
	if (ft_print_state_change(philo, SLEEP) != 0)
		return (1);
	if (myusleep(philo->data->time_to_sleep, philo) != 0)
		return (1);
	return (0);
}

int	think(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock);
	if (philo->data->death != 0)
	{
		pthread_mutex_unlock(&philo->data->lock);
	}
	else
		pthread_mutex_unlock(&philo->data->lock);
	if (ft_print_state_change(philo, THINK) != 0)
		return (1);
	return (0);
}
