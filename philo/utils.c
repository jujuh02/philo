/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhaamid <juhaamid@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:40:30 by juhaamid          #+#    #+#             */
/*   Updated: 2023/08/29 16:26:37 by juhaamid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	kms(t_philo *philo)
{
	long long	elapsed_time;

	elapsed_time = get_time() - philo->data->time;
	pthread_mutex_lock(&philo->data->pop_mutex);
	if (philo->data->time_to_die < elapsed_time - philo->timeoflastmeal)
	{
		pthread_mutex_unlock(&philo->data->pop_mutex);
		pthread_mutex_lock(&philo->data->lock);
		if (philo->data->death == 1)
		{
			pthread_mutex_unlock(&philo->data->lock);
			return (true);
		}
		philo->data->death = 1;
		pthread_mutex_unlock(&philo->data->lock);
		pthread_mutex_lock(&philo->data->print);
		printf(RED"%lld %d died\n",
			get_time() - philo->data->time, philo->numphilo + 1);
		pthread_mutex_unlock(&philo->data->print);
		return (true);
	}
	pthread_mutex_unlock(&philo->data->pop_mutex);
	return (false);
}

int	myusleep(int time, t_philo *philo)
{
	long long	current_time;

	current_time = get_time();
	pthread_mutex_lock(&philo->data->lock);
	while (time > get_time() - current_time && philo->data->death == 0)
	{
		pthread_mutex_unlock(&philo->data->lock);
		kms(philo);
		if (usleep(100) == -1)
			return (2);
		pthread_mutex_lock(&philo->data->lock);
	}
	pthread_mutex_unlock(&philo->data->lock);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int			neg;
	long int	nbr;
	int			bop;

	neg = 1;
	nbr = 0;
	bop = 0;
	while ((nptr[bop] == ' ' || (nptr[bop] >= 9 && nptr[bop] <= 13)))
		bop++;
	if (nptr[bop] == '-' || nptr[bop] == '+')
	{
		if (nptr[bop] == '-')
			neg *= -1;
		bop++;
	}
	while (nptr[bop] >= '0' && nptr[bop] <= '9')
	{
		nbr = nbr * 10 + nptr[bop] - '0';
		bop++;
		if (nbr > 1844674407370955169 && neg == 1)
			return (-1);
		if (nbr > 1844674407370955169 && neg == -1)
			return (0);
	}
	return (neg * nbr);
}

int	check_spaces_only(int c)
{
	if (c == ' ' || c == '\t')
		return (1);
	else
		return (0);
}

int	check_empty_input(char **av)
{
	int	a;
	int	b;

	a = 1;
	b = 0;
	while (av[a])
	{
		b = 0;
		while (av[a][b])
		{
			if (check_spaces_only(av[a][b]))
				return (1);
			b++;
		}
		a++;
	}
	return (0);
}
