/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 16:02:03 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/09/21 11:37:08 by aandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#ifndef MAIN_H
# define MAIN_H

#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdint.h>


/* ================ ~ STRUCTURES ~ ================ */

typedef enum	e_bool
{
	false,
	true
}				t_bool;

typedef struct	s_data
{
	struct s_philo	**philo_array;
	pthread_mutex_t	*forks_array;
	pthread_mutex_t	display_perm;
	pthread_mutex_t	rw_perm;
	int				philo_nb;
	int				time_zero;
	int				time_to_die;
	int				time_to_eat;
	int 			time_to_sleep;
	int				meals_nb;
	t_bool			end_program;
}				t_data;

typedef struct	s_philo
{
	int				id;
	t_data			*data;
	int				last_meal;
	int				start_time;
	pthread_t		thread;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	*fork_r;
}				t_philo;

/* ================ ~ UTILS ~ ================ */
size_t	ft_strlen(const char *str);
int		ft_atoi(const char *str);
t_bool	check_end_program(t_philo *philo);

/* ================ ~ PARSING ~ ================ */
t_bool	check_input(int ac, char **av);

/* ================ ~ PHILO ~ ================ */
t_philo **philo_create_array(t_data *data);
void	philo_join_all(t_philo **philo_array);
void	philo_free(t_philo **philo_array, int philo_nb);

/* ================ ~ DATA ~ ================ */
t_data	*data_init(int ac, char **av);
void	data_free(t_data *data);

/* ================ ~ ROUTINE ~ ================ */
void	*routine(void* arg);
int		get_time(void);
void	ft_usleep(unsigned int time, t_philo *philo);

#endif