/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhaamid <juhaamid@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:13:51 by juhaamid          #+#    #+#             */
/*   Updated: 2023/08/24 12:30:33 by juhaamid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	long	get_time(void)
{
	struct timeval	t_second;

	if (gettimeofday(&t_second, NULL) == -1)
		ft_error();
	return ((t_second.tv_sec * 1000) + (t_second.tv_usec / 1000));
}

int main(int ac, char **av)
{
    t_data *table;
    
    if (ac < 5 || ac > 6)
    {
        printf(RED"Wrong num of arguments :( \n");
        return (1);
    }
    if (!inputchecker(ac, av))
        instructions();
    table = settable(av);
    if (!table)
        return(EXIT_FAILURE);
    initphilo(&table);
    start(&table);
}