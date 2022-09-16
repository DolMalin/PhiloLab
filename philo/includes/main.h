/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdal-mol <dolmalinn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 16:02:03 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/09/16 17:18:21 by pdal-mol         ###   ########.fr       */
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
	pthread_mutex_t	write_perm;
	int				philo_nb;
	int				time_to_die;
	int				time_to_eat;
	int 			time_to_sleep;
	int				meals_nb;
}				t_data;

typedef struct	s_philo
{
	int				id;
	t_data			*data;
	pthread_t		thread;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	*write_perm;
}				t_philo;

/* ================ ~ UTILS ~ ================ */
size_t	ft_strlen(const char *str);
int		ft_atoi(const char *str);

/* ================ ~ PARSING ~ ================ */
t_bool	check_input(int ac, char **av);

/* ================ ~ PHILO ~ ================ */
t_philo **philo_create_array(t_data *data);
void	philo_free(t_philo **philo_array, int philo_nb);

/* ================ ~ DATA ~ ================ */
t_data	*data_init(int ac, char **av);
void	data_free(t_data *data);

/* ================ ~ ROUTINE ~ ================ */
void	*routine(void* arg);

#endif