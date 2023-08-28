/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhaamid <juhaamid@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:13:51 by juhaamid          #+#    #+#             */
/*   Updated: 2023/08/28 11:42:11 by juhaamid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free(t_data *all)
{
	int	i;

	i = -1;
	
	pthread_mutex_destroy(&all->lock);
	// pthread_mutex_destroy(&all->meal_mutex);
	// pthread_mutex_destroy(&all->meal_count_mutex);
	while (++i < all->number_of_philosophers)
	{
		pthread_mutex_destroy(&all->fork[i]);
	}
	free(all);
	return ;
}

long long 	get_time(void)
{
	struct timeval	t_second;
	long long time;

	gettimeofday(&t_second, NULL);
	time = (t_second.tv_sec * 1000) + (t_second.tv_usec / 1000);
	return (time);
}


int main(int ac, char **av)
{
	t_data *table;
	table = malloc(sizeof(t_data));
	if (!table)
		return(0);
	if (ac < 5 || ac > 6)
	{
		printf(RED"Wrong num of arguments :( \n");
		return (1);
	}
	// if (!inputchecker(av))
	//     instructions();
	if (settable(av, table) != 0)
	{
		free(table);
		return(1);
	}
	// table->time = get_time();
	// if (table->time == -1) 
	// 	return(1);
	if (ft_init_mutexes(table) != 0)
		return(2);
	if (initphilo(table)  != 0)
		return (3);
	if (start(table) != 0)
		return(2);
	ft_free(table);
}