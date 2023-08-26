/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhaamid <juhaamid@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 08:48:28 by juhaamid          #+#    #+#             */
/*   Updated: 2023/08/26 15:49:33 by juhaamid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

# define GRAB_FORK  0
# define EAT		1
# define SLEEP		2
# define THINK		3
# define DIE		4

typedef struct s_philo
{
	int					numphilo;
	pthread_t			ph;
	int					flag;
	int					right;
	int					left;
	int					meal;
	long long			timeoflastmeal;
	struct s_data		*data;
}t_philo;

typedef struct s_data
{
	t_philo				*philo;
	pthread_mutex_t		lock;
	pthread_mutex_t		*fork;
	pthread_mutex_t		print;
	int					number_of_philosophers;
	long long			time_to_die;
	long long			time_to_eat;
	long long			time_to_sleep;
	long long			number_of_times_each_philosopher_must_eat;
	int					death;
	long long			time;
	int					*sign;
	pthread_mutex_t		meal_mutex;
	pthread_mutex_t		meal_count_mutex;
	
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
int		ft_atoi(const char *nptr);
void	instructions(void);
int		inputchecker(char **av);
void	status(t_philo *philo, char *s, int i);
int	myusleep(int time, t_philo *philo);

// *************setup file***************//
// t_data	*settable(char **av);
int	settable(char **av, t_data *table);
int	start(t_data *table);
void    *routine(void *arg);
int    initphilo(t_data *table);
int	ft_init_mutexes(t_data *table);

// *************routine file**************//
void  eat(t_philo *philo, int id);
int	sleeeep(t_philo *philo);
int	think(t_philo *philo);
int	ft_unlock_and_join(t_data *table, pthread_t *pthread);
int	ft_handle_lonely_philo(t_philo *philo);
int	ft_loop_main_thread(t_data *table);

// *************utils2 file****************//
int is_dead(t_data *table);
int	ft_routine_is_finished(t_data *table);
int	ft_print_state_change(t_philo *philo, int state);
void	*death(t_philo *philo);

#endif