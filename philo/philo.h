/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhaamid <juhaamid@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 08:48:28 by juhaamid          #+#    #+#             */
/*   Updated: 2023/08/29 16:37:04 by juhaamid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>

# define GRAB_FORK  0
# define GRAB_FORKL 5
# define EAT		1
# define SLEEP		2
# define THINK		3
# define DIE		4

typedef struct s_philo
{
	int					numphilo;
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
	long long			num_of_tepme;
	int					death;
	long long			time;
	int					*sign;
	int					*avail;
	pthread_mutex_t		pop_mutex;
	pthread_mutex_t		meal_count_mutex;

}t_data;

// **********colors**************//
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define GREEN "\033[0;32m"
# define RED "\033[0;31m"
# define YELLOW "\033[0;33m"
# define WHITE "\033[0;37m"

// *********philo file*******//
long	long	get_time(void);

// ***********utils file************//

void		status(t_philo *philo, char *s, int i);
int			myusleep(int time, t_philo *philo);
int			kms(t_philo *philo);
int			check_empty_input(char **av);

// *************setup file***************//
int			settable(char **av, t_data *table);
int			start(t_data *table);
void		*routine(void *arg);
int			initphilo(t_data *table);
int			ft_init_mutexes(t_data *table);

// *************eat file**************//
void		eat(t_philo *philo, int id);
int			take_forks(t_philo *philo, int i);
int			odd(t_philo *philo, int i, int left);
int			even(t_philo *philo, int i, int left);

// *************routine2 file *************//
int			ft_loop_main_thread(t_data *table);
int			ft_unlock_and_join(t_data *table, pthread_t *pthread);
int			ft_handle_lonely_philo(t_philo *philo);
int			sleeeep(t_philo *philo);
int			think(t_philo *philo);

// *************utils2 file****************//
int			is_dead(t_data *table);
int			ft_routine_is_finished(t_data *table);
int			routine_check(int full, t_data *table);
int			ft_print_state_change(t_philo *philo, int state);
void		ft_cont_print(t_philo *philo, int state);

// **************parsing file***************//
int			ft_isalpha(int c);
int			inputchecker(int ac, char **av);
int			ft_atoi(const char *nptr);
void		instructions(void);

#endif