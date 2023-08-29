/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhaamid <juhaamid@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 11:46:53 by juhaamid          #+#    #+#             */
/*   Updated: 2023/08/28 16:53:13 by juhaamid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	ft_print_state_change(t_philo *philo, int state)
{
	if (pthread_mutex_lock(&philo->data->print) != 0)
		return (1);
	if (pthread_mutex_lock(&philo->data->lock) != 0)
		return (1);
	if (philo->data->death == 0)
	{
		if (state == GRAB_FORK)
			printf(CYAN"%lld %d has taken right fork\n",
				get_time() - philo->data->time, philo->numphilo + 1);
		else if (state == GRAB_FORKL)
			printf(CYAN"%lld %d has taken left fork\n",
				get_time() - philo->data->time, philo->numphilo+ 1);
		else if (state == EAT)
			printf(GREEN"%lld %d is eating\n",
				get_time() - philo->data->time, philo->numphilo+ 1);
		else if (state == SLEEP)
			printf(PURPLE"%lld %d is sleeping\n",
				get_time() - philo->data->time, philo->numphilo+ 1);
		else if (state == THINK)
			printf(YELLOW"%lld %d is thinking\n",
				get_time() - philo->data->time, philo->numphilo+ 1);
		else if (state == DIE)
			printf(RED"%lld %d died\n",
				get_time() - philo->data->time, philo->numphilo+ 1);
	}
	// if (state != DIE)
	if (pthread_mutex_unlock(&philo->data->print) != 0)
		return(2);
	if (pthread_mutex_unlock(&philo->data->lock) != 0)
		return (1);
	return (0);
}



int	ft_routine_is_finished(t_data *table)
{
	int	i;
	int	num_philos_full;

	i = -1;
	num_philos_full = 0;
	if (table->number_of_times_each_philosopher_must_eat == -1)
		return (0);
	while (++i < table->number_of_philosophers)
	{
		if (pthread_mutex_lock(&table->pop_mutex) != 0)
			return (0);
		if (table->philo[i].meal >= table->number_of_times_each_philosopher_must_eat)
		{
			num_philos_full++;
			if (pthread_mutex_unlock(&table->pop_mutex) != 0)
				return (0);
		}
		else
		{
			if (pthread_mutex_unlock(&table->pop_mutex) != 0)
			return (0);
			break ;
		}
	}
	if (num_philos_full >= table->number_of_philosophers)
	{
		if (pthread_mutex_lock(&table->lock) != 0)
			return (4);
		table->death = 1;
		if (pthread_mutex_unlock(&table->lock) != 0)
			return (3);
		return (1);
	}
	return (0);
}

int is_dead(t_data *table)
{
	int	i;

	i = -1;
	while (++i < table->number_of_philosophers)
	{
		if (kms(&table->philo[i]) == true)
			return (1);
	}
	return (0);
}

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}
