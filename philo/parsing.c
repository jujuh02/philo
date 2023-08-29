/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhaamid <juhaamid@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 11:35:23 by juhaamid          #+#    #+#             */
/*   Updated: 2023/08/29 13:38:15 by juhaamid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	argv_sign(char **av)
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
			if (b == 0)
			{
				if (av[a][b] == '+' || av[a][b] == '-')
					b++;
			}
			if (!(av[a][b] >= '0' && av[a][b] <= '9'))
			{
				return (1);
			}
			b++;
		}
		a++;
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
	if (ac < 5 || ac > 6)
		return (1);
	if (check_empty_input(av) == 1 || argv_alphabet(av) == 1 
		|| argv_sign(av) == 1)
		return (1);
	return (0);
}

void	instructions(void)
{
	printf(RED "\n                 UH OH :-(      \n");
	printf(RED "             WRONG INPUT-> TRY:\n");
	printf(GREEN "./philo || # of philos || timetodie || timetoeat || ");
	printf(GREEN "timetosleep || --->> (OPTIONAL) # of timesphiloeats\n");
	printf(GREEN "\nexample: ./philo 3 400 200 200 3\n");
}
