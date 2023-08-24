/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhaamid <juhaamid@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:40:30 by juhaamid          #+#    #+#             */
/*   Updated: 2023/08/24 12:06:18 by juhaamid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

void	myusleep(int time)
{
	long long	t;

	t = get_time();
	while (get_time() - t < (long int)time)
		usleep(10);
}

void	status(t_philo *philo, char *s, int i)
{
	pthread_mutex_lock(&philo->data->mutex);
	printf("%lld %d %s\n", get_time() - philo->data->time, philo->numphilo, s);
	if (i)
		pthread_mutex_unlock(&philo->data->lock);
}

int	inputchecker(int ac, char **av)
{
	int i;
	int k;
	
	i = 1;
	while (i < ac)
	{
		k = 0;
		while (av[i][k])
		{
			if (av[i][k] < '0' || av[i][k] > '9')
				return (1);
			k++;
		}
		i++;
	}
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
3	while ((nptr[bop] == ' ' || (nptr[bop] >= 9 && nptr[bop] <= 13)))
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

void	instructions(void)
{
	printf(RED "\n                 UH OH :-(      \n");
	printf(RED "             WRONG INPUT-> TRY:\n");
	printf(GREEN "./philo || # of philos || timetodie || timetoeat || ");
	printf(GREEN "timetosleep || # of timesphiloeats\n");
	printf(GREEN "\nexample: ./philo 3 400 200 200 3\n");
}