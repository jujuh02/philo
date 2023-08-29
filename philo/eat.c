/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhaamid <juhaamid@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 14:09:51 by juhaamid          #+#    #+#             */
/*   Updated: 2023/08/29 16:44:35 by juhaamid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	odd(t_philo *philo, int i, int left)
{
	pthread_mutex_lock(&philo->data->fork[left]);
	pthread_mutex_lock(&philo->data->fork[i]);
	if (philo->data->avail[left] == 1 && philo->data->avail[i] == 1 
		&& philo->data->sign[left] != i && philo->data->sign[i] != i)
	{
		philo->data->avail[i] = 0;
		philo->data->avail[left] = 0;
		pthread_mutex_unlock(&philo->data->fork[left]);
		pthread_mutex_unlock(&philo->data->fork[i]);
		if (ft_print_state_change(philo, GRAB_FORK) != 0)
			return (0);
		if (ft_print_state_change(philo, GRAB_FORKL) != 0)
			return (0);
		eat(philo, philo->numphilo);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->fork[i]);
		pthread_mutex_unlock(&philo->data->fork[left]);
	}
	return (0);
}

int	even(t_philo *philo, int i, int left)
{
	pthread_mutex_lock(&philo->data->fork[i]);
	pthread_mutex_lock(&philo->data->fork[left]);
	if (philo->data->avail[left] == 1 && philo->data->avail[i] == 1
		&& philo->data->sign[left] != i && philo->data->sign[i] != i)
	{
		philo->data->avail[i] = 0;
		philo->data->avail[left] = 0;
		pthread_mutex_unlock(&philo->data->fork[i]);
		pthread_mutex_unlock(&philo->data->fork[left]);
		if (ft_print_state_change(philo, GRAB_FORKL) != 0)
			return (0);
		if (ft_print_state_change(philo, GRAB_FORK) != 0)
			return (0);
		eat(philo, philo->numphilo);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->fork[i]);
		pthread_mutex_unlock(&philo->data->fork[left]);
	}
	return (0);
}

int	take_forks(t_philo *philo, int i)
{
	int	left;

	left = (i + 1) % philo->data->number_of_philosophers;
	if (i % 2 == 0)
	{
		if (even(philo, i, left) == 1)
			return (1);
	}
	else
	{
		if (odd(philo, i, left) == 1)
			return (1);
	}
	return (0);
}

static void	put_forks(t_philo *philo, int i)
{
	int	left;

	left = (i + 1) % philo->data->number_of_philosophers;
	if (i % 2 == 0)
	{
		pthread_mutex_lock(&philo->data->fork[i]);
		pthread_mutex_lock(&philo->data->fork[left]);
		philo->data->avail[i] = 1;
		philo->data->avail[left] = 1;
		philo->data->sign[left] = i;
		philo->data->sign[i] = i;
		pthread_mutex_unlock(&philo->data->fork[i]);
		pthread_mutex_unlock(&philo->data->fork[left]);
	}
	else
	{
		pthread_mutex_lock(&philo->data->fork[left]);
		pthread_mutex_lock(&philo->data->fork[i]);
		philo->data->avail[left] = 1;
		philo->data->avail[i] = 1;
		philo->data->sign[left] = i;
		philo->data->sign[i] = i;
		pthread_mutex_unlock(&philo->data->fork[left]);
		pthread_mutex_unlock(&philo->data->fork[i]);
	}
}

void	eat(t_philo *philo, int id)
{
	if (ft_print_state_change(philo, EAT) != 0)
		return ;
	pthread_mutex_lock(&philo->data->pop_mutex);
	philo->meal++;
	pthread_mutex_unlock(&philo->data->pop_mutex);
	myusleep(philo->data->time_to_eat, philo);
	pthread_mutex_lock(&philo->data->pop_mutex);
	philo->timeoflastmeal = get_time() - philo->data->time ;
	pthread_mutex_unlock(&philo->data->pop_mutex);
	put_forks(philo, id);
}
