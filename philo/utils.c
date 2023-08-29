/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhaamid <juhaamid@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:40:30 by juhaamid          #+#    #+#             */
/*   Updated: 2023/08/29 11:14:25 by juhaamid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

int	kms(t_philo *philo)
{
	long long	elapsed_time;

	elapsed_time = get_time() - philo->data->time;
	if (pthread_mutex_lock(&philo->data->pop_mutex) != 0)
		return (1);
	if (philo->data->time_to_die < elapsed_time - philo->timeoflastmeal)
	{
		if (pthread_mutex_unlock(&philo->data->pop_mutex) != 0)
			return (1);
		if (pthread_mutex_lock(&philo->data->lock) != 0)
				return (2);
			if (philo->data->death == 1)
			{
				if (pthread_mutex_unlock(&philo->data->lock) != 0)
					return (2);
				return (true);
			}
			philo->data->death = 1;
			if (pthread_mutex_unlock(&philo->data->lock) != 0)
				return (2);
			if (pthread_mutex_lock(&philo->data->print) != 0)
				return (2);
			printf(RED"%lld %d died\n",
				get_time() - philo->data->time, philo->numphilo+ 1);
			if (pthread_mutex_unlock(&philo->data->print) != 0)
				return (2);
		return (true);
	}
	if (pthread_mutex_unlock(&philo->data->pop_mutex) != 0)
			return (1);
	return (false);
	
}

int	myusleep(int time, t_philo *philo)
{
	long long 	current_time;

	current_time = get_time();
	if (pthread_mutex_lock(&philo->data->lock) != 0)
		return (1);
	while (time > get_time() - current_time && philo->data->death == 0)
	{
		if (pthread_mutex_unlock(&philo->data->lock) != 0)
			return (1);
		kms(philo);
		if (usleep(1000) == -1)
			return (2);
		if (pthread_mutex_lock(&philo->data->lock) != 0)
			return (1);
	}
	if (pthread_mutex_unlock(&philo->data->lock) != 0)
		return (1);
	return (0);
}

int	argv_alphabet(char **av)
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
			if (ft_isalpha(av[a][b]))
				return (1);
			b++;
		}
		a++;
	}
	return (0);
}


int	inputchecker(int ac, char **av)
{
	(void)ac;
	if (argv_alphabet(av) == 1)
		return (1);
	return (0);
}


// int	inputchecker(int ac, char **av)
// {
// 	int i;
// 	int k;
	
// 	i = 1;
// 	if (argv_alphabet(av) == 1)
// 		return(1);
// 	while (i < ac)
// 	{
// 		k = 0;
// 		while (av[i][k])
// 		{
// 			if (av[i][k] < '0' || av[i][k] > '9')
// 				return (1);
// 			k++;
// 		}
// 		i++;
// 	}
// 	return (0);
// }

// int	inputchecker(char **av)
// {
// 	int	i;

// 	i = 1;
// 	while (av[i])
// 	{
// 		if (ft_atoi(av[i]) <= 0)
// 		{
// 			printf("eh eh");
// 			return (1);
// 		}
// 		i++;
// 	}
// 	return (0);
// }


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

void	instructions(void)
{
	printf(RED "\n                 UH OH :-(      \n");
	printf(RED "             WRONG INPUT-> TRY:\n");
	printf(GREEN "./philo || # of philos || timetodie || timetoeat || ");
	printf(GREEN "timetosleep || --->> (OPTIONAL) # of timesphiloeats\n");
	printf(GREEN "\nexample: ./philo 3 400 200 200 3\n");
}