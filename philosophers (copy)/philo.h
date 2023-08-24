/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhaamid <juhaamid@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 08:48:28 by juhaamid          #+#    #+#             */
/*   Updated: 2023/08/24 12:32:38 by juhaamid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <pthread.h>

typedef struct s_philo
{
	int			numphilo;
	pthread_t	ph;
	int			flag;
	t_data		*data;
}t_philo;

typedef struct s_data
{
	t_philo				*philo;
	// t_fork				*fork;
	pthread_mutex_t		lock;
	pthread_mutex_t		print;
	pthread_mutex_t		dead;
	pthread_mutex_t		*fork;
	int					number_of_philosophers;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_times_each_philosopher_must_eat;
	int					death;
	int					time
	long long			*last_eat;
	
	
}t_data;

// **********colors**************//
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define GREEN "\033[0;32m"
# define RED "\033[0;31m"
# define YELLOW "\033[0;33m"

// *********philo file*******//
long	long	get_time(void);

// ***********utils file************//
int	ft_atoi(const char *nptr);
void	instructions(void);
int	inputchecker(int ac, char **av);
void	status(t_philo *philo, char *s, int i);
void	myusleep(int time);

// *************setup file***************//
t_data *settable(char **av);
void	start(t_data *table);
void    *routine(void *arg);
int    initphilo(t_data *table);

// *************routine file**************//
void    eat(t_philo *philo);
void	sleep(t_philo *philo);
void	think(t_philo *philo);
void    *is_dead(t_philo *philo);


#endif