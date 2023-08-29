/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhaamid <juhaamid@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 11:46:53 by juhaamid          #+#    #+#             */
/*   Updated: 2023/08/29 17:06:05 by juhaamid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_cont_print(t_philo *philo, int state)
{
	if (state == SLEEP)
		printf(PURPLE"%lld %d is sleeping\n",
			get_time() - philo->data->time, philo->numphilo + 1);
	else if (state == THINK)
		printf(YELLOW"%lld %d is thinking\n",
			get_time() - philo->data->time, philo->numphilo + 1);
	else if (state == DIE)
		printf(RED"%lld %d died\n",
			get_time() - philo->data->time, philo->numphilo + 1);
}

int	ft_print_state_change(t_philo *philo, int state)
{
	pthread_mutex_lock(&philo->data->print);
	pthread_mutex_lock(&philo->data->lock);
	if (philo->data->death == 0)
	{
		if (state == GRAB_FORK)
			printf(CYAN"%lld %d has taken a fork\n",
				get_time() - philo->data->time, philo->numphilo + 1);
		else if (state == GRAB_FORKL)
			printf(WHITE"%lld %d has taken a fork\n",
				get_time() - philo->data->time, philo->numphilo + 1);
		else if (state == EAT)
			printf(GREEN"%lld %d is eating\n",
				get_time() - philo->data->time, philo->numphilo + 1);
		else
			ft_cont_print(philo, state);
	}
	pthread_mutex_unlock(&philo->data->print);
	pthread_mutex_unlock(&philo->data->lock);
	return (0);
}

int	routine_check(int full, t_data *table)
{
	if (full >= table->number_of_philosophers)
	{
		pthread_mutex_lock(&table->lock);
		table->death = 1;
		pthread_mutex_unlock(&table->lock);
		return (1);
	}
	return (0);
}

int	ft_routine_is_finished(t_data *table)
{
	int	i;
	int	num_philos_full;

	i = -1;
	num_philos_full = 0;
	if (table->num_of_tepme == -1)
		return (0);
	while (++i < table->number_of_philosophers)
	{
		pthread_mutex_lock(&table->pop_mutex);
		if (table->philo[i].meal >= table->num_of_tepme)
		{
			num_philos_full++;
			pthread_mutex_unlock(&table->pop_mutex);
		}
		else
		{
			pthread_mutex_unlock(&table->pop_mutex);
			break ;
		}
	}
	if (routine_check(num_philos_full, table) == 1)
		return (1);
	return (0);
}

int	is_dead(t_data *table)
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
