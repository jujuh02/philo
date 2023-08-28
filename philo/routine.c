/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhaamid <juhaamid@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 10:21:46 by juhaamid          #+#    #+#             */
/*   Updated: 2023/08/28 13:16:56 by juhaamid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	ft_loop_main_thread(t_data *table)
{
	if (pthread_mutex_lock(&table->pop_mutex) != 0)
		return (1);
	while (table->death == 0)
	{
		if (pthread_mutex_unlock(&table->pop_mutex) != 0)
		return (1);
		if (ft_routine_is_finished(table) == 1)
			return (0);
		if (is_dead(table) == 1)
			return (1);
		if (pthread_mutex_lock(&table->pop_mutex) != 0)
			return (1);
	}
	if (pthread_mutex_unlock(&table->pop_mutex) != 0)
		return (1);
	return (0);
}

int	ft_handle_lonely_philo(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	// if (pthread_mutex_lock(&data->fork[philo->left]) != 0)
	// 	return (2);
	if (ft_print_state_change(philo, GRAB_FORK) != 0)
		return (1);
	if (myusleep(data->time_to_die, philo) != 0)
		return (1);
	// if (pthread_mutex_unlock(&data->fork[philo->left]) != 0)
	// 	return (3);
	return (0);
}


int	ft_unlock_and_join(t_data *table, pthread_t *pthread)
{
	int	i;

	// if (pthread_mutex_unlock(&table->print) != 0)
	// {
	// 	free(pthread);
	// 	return (1);
	// }
	// // if (pthread_mutex_unlock(&table->lock) != 0)
	// {
	// 	free(pthread);
	// 	return (1);
	// }
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


int	take_forks(t_philo *philo, int i)
{
	int	left;

	left = (i + 1) % philo->data->number_of_philosophers;
		// pthread_mutex_lock(&philo->data->print);
		// printf("ID-%d   F-%d  %d\n", i, left, i);
		// pthread_mutex_unlock(&philo->data->print);
	if (i % 2 == 0)
	{
		pthread_mutex_lock(&philo->data->fork[i]);
		pthread_mutex_lock(&philo->data->fork[left]);
		if (philo->data->avail[left] == 1 && philo->data->avail[i] && philo->data->sign[left] != i && philo->data->sign[i]!= i)
		{
			philo->data->avail[i] = 0;
			philo->data->avail[left] = 0;
			// philo->data->sign[left] = i;
			//  philo->data->sign[i] = i;
			pthread_mutex_unlock(&philo->data->fork[i]);
			pthread_mutex_unlock(&philo->data->fork[left]);
			if (ft_print_state_change(philo, GRAB_FORKL) != 0)
			return (0);
			if (ft_print_state_change(philo, GRAB_FORK) != 0)
			return (0);
			eat(philo, philo->numphilo);
			return(1);
		}
		else
		{
			pthread_mutex_unlock(&philo->data->fork[i]);
			pthread_mutex_unlock(&philo->data->fork[left]);
			// myusleep(0, philo);
			
		}
	}
	else
	{
		pthread_mutex_lock(&philo->data->fork[left]);
		pthread_mutex_lock(&philo->data->fork[i]);
		if (philo->data->avail[left] == 1 && philo->data->avail[i] == 1 && philo->data->sign[left] != i && philo->data->sign[i]!= i)
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
			// myusleep(0, philo);
		}	
	}
	return(0);
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
	// take_forks(philo, id);
	if (ft_print_state_change(philo, EAT) != 0)
			return ;
	myusleep(philo->data->time_to_eat, philo);
	if (pthread_mutex_lock(&philo->data->pop_mutex) != 0)
			return ;
	philo->meal++;
	philo->timeoflastmeal = get_time() - philo->data->time ;
	if (pthread_mutex_unlock(&philo->data->pop_mutex) != 0)
			return ;
	// philo->timeoflastmeal = get_time() - philo->data->time ;
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
	if (pthread_mutex_lock(&philo->data->lock) != 0)
		return (1);
	if (philo->data->death != 0)
	{
		if (pthread_mutex_unlock(&philo->data->lock) != 0)
			return (1);
		return (0);
	}
	if (pthread_mutex_unlock(&philo->data->lock) != 0)
		return (1);
	if (ft_print_state_change(philo, SLEEP) != 0)
		return (1);
	if (myusleep(philo->data->time_to_sleep, philo) != 0)
		return (1);
	return (0);
}

int	think(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->data->lock) != 0)
		return (1);
	if (philo->data->death != 0)
	{
	if (pthread_mutex_unlock(&philo->data->lock) != 0)
			return (1);
		return (0);
	}
	if (pthread_mutex_unlock(&philo->data->lock) != 0)
		return (1);
	if (ft_print_state_change(philo, THINK) != 0)
		return (1);
	return (0);
}
