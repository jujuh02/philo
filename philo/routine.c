/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhaamid <juhaamid@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 10:21:46 by juhaamid          #+#    #+#             */
/*   Updated: 2023/08/26 16:20:52 by juhaamid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	ft_loop_main_thread(t_data *table)
{
	while (table->death == 0)
	{
		if (ft_routine_is_finished(table) == 1)
			return (0);
		if (is_dead(table) == 1)
			return (1);
	}
	return (0);
}

int	ft_handle_lonely_philo(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (pthread_mutex_lock(&data->fork[philo->left]) != 0)
		return (2);
	if (ft_print_state_change(philo, GRAB_FORK) != 0)
		return (1);
	if (myusleep(data->time_to_die, philo) != 0)
		return (1);
	if (pthread_mutex_unlock(&data->fork[philo->left]) != 0)
		return (3);
	return (0);
}


int	ft_unlock_and_join(t_data *table, pthread_t *pthread)
{
	int	i;

	if (pthread_mutex_unlock(&table->print) != 0)
	{
		free(pthread);
		return (1);
	}
	if (pthread_mutex_unlock(&table->lock) != 0)
	{
		free(pthread);
		return (1);
	}
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


 int	ft_unlock_forks(t_philo *philo)
{
	if (pthread_mutex_unlock(&philo->data->fork[philo->left])
		!= 0)
		return (4);
	if (pthread_mutex_unlock(&philo->data->fork[philo->right])
		!= 0)
		return (3);
	return (0);
}


static void	take_forks(t_philo *philo, int i)
{
	int	left;

	left = (i + 1) % philo->data->number_of_philosophers;
	if (i % 2 == 0)
	{
		pthread_mutex_lock(&philo->data->fork[left]);
		if (ft_print_state_change(philo, GRAB_FORK) != 0)
			return ;
		pthread_mutex_lock(&philo->data->fork[i]);
		if (ft_print_state_change(philo, GRAB_FORK) != 0)
			return ;
	}
	else
	{
		pthread_mutex_lock(&philo->data->fork[i]);
		if (ft_print_state_change(philo, GRAB_FORK) != 0)
			return ;
		pthread_mutex_lock(&philo->data->fork[left]);
		if (ft_print_state_change(philo, GRAB_FORK) != 0)
			return ;
	}
}

static void	put_forks(t_philo *philo, int i)
{
	int	left;

	left = (i + 1) % philo->data->number_of_philosophers;
	if (i % 2 == 0)
	{
		pthread_mutex_unlock(&philo->data->fork[i]);
		pthread_mutex_unlock(&philo->data->fork[left]);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->fork[left]);
		pthread_mutex_unlock(&philo->data->fork[i]);
	}
}

void	eat(t_philo *philo, int id)
{
	take_forks(philo, id);
	// pthread_mutex_lock(&philo->data->meal_mutex);
	// pthread_mutex_unlock(&philo->data->meal_mutex);
	if (ft_print_state_change(philo, EAT) != 0)
			return ;
	myusleep(philo->data->time_to_eat, philo);
	pthread_mutex_lock(&philo->data->meal_count_mutex);
	philo->meal++;
	pthread_mutex_unlock(&philo->data->meal_count_mutex);
	philo->timeoflastmeal = get_time() - philo->data->time ;
	put_forks(philo, id);
}

// int	eat(t_philo *philo, int id)
// {
// 	t_data	*data;

// 	data = philo->data;
// 	if (data->death != 0)
// 		return (-1);
// 	if (pthread_mutex_lock(&data->fork[philo->left]) != 0)
// 		return (2);
// 	if (ft_print_state_change(philo, GRAB_FORK) != 0)
// 		return (1);
// 	if (pthread_mutex_lock(&data->fork[philo->right]) != 0)
// 		return (2);
// 	if (data->death == 0)
// 	{
// 		if (ft_print_state_change(philo, GRAB_FORK) != 0)
// 			return (1);
// 		philo->timeoflastmeal = get_time() - data->time;
// 		if (ft_print_state_change(philo, EAT) != 0)
// 			return (1);
// 		if (myusleep(philo->data->time_to_eat) != 0)
// 			return (1);
// 		philo->meal++;
// 	}
// 	if (ft_unlock_forks(philo) != 0)
// 		return (1);
// 	return (0);
// }

int	sleeeep(t_philo *philo)
{
	if (philo->data->death != 0)
		return (-1);
	if (ft_print_state_change(philo, SLEEP) != 0)
		return (1);
	if (myusleep(philo->data->time_to_sleep, philo) != 0)
		return (1);
	return (0);
}

int	think(t_philo *philo)
{
	if (philo->data->death != 0)
		return (-1);
	if (ft_print_state_change(philo, THINK) != 0)
		return (1);
	return (0);
}
