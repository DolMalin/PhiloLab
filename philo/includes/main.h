/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdal-mol <dolmalinn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 16:02:03 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/09/16 12:50:53 by pdal-mol         ###   ########.fr       */
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
	int				philo_nb;
	int				time_to_die;
	int				time_to_eat;
	int 			time_to_sleep;
	int				meals_nb;
}				t_data;

/* ================ ~ UTILS ~ ================ */
size_t	ft_strlen(const char *str);
int		ft_atoi(const char *str);

/* ================ ~ PARSING ~ ================ */
t_bool	check_input(int ac, char **av);


#endif