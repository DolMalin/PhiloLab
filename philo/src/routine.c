/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:38:56 by pdal-mol          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/09/21 13:30:52 by aandric          ###   ########lyon.fr   */
=======
/*   Updated: 2022/09/20 17:50:21 by pdal-mol         ###   ########.fr       */
>>>>>>> 837ba01 (fix(mutex): last_meal mutex is now unique for each philosopher and not shared anymore with other philos but only with main)
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"


void	display(t_philo *philo, const char *str)
{	
	if (check_end_program(philo))
		return ;
	pthread_mutex_lock(&philo->data->display_perm);
	printf("%d %d %s\n", get_time() - philo->start_time, philo->id, str);
	pthread_mutex_unlock(&philo->data->display_perm);
}

void	routine_eat(t_philo *philo)
{
	int last_meal;
	// if (check_end_program(philo))
		// return ;
	pthread_mutex_lock(philo->fork_l);
	display(philo, "has taken a fork");
	pthread_mutex_lock(philo->fork_r);
	display(philo, "has taken a fork");
	display(philo, "is eating");
	last_meal = get_time();
	
<<<<<<< HEAD
	pthread_mutex_lock(&philo->data->rw_perm);
	philo->last_meal = get_time() - philo->data->time_zero;
	pthread_mutex_unlock(&philo->data->rw_perm);
=======
	pthread_mutex_lock(&philo->last_meal_perm);
	philo->last_meal = last_meal;
	pthread_mutex_unlock(&philo->last_meal_perm);
>>>>>>> 837ba01 (fix(mutex): last_meal mutex is now unique for each philosopher and not shared anymore with other philos but only with main)
	
	ft_usleep(philo->data->time_to_eat, philo);
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
}

void	routine_sleep(t_philo *philo)
{
	// if (check_end_program(philo))
		// return ;
	display(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep, philo);
}

void	routine_think(t_philo *philo)
{
	// if (check_end_program(philo))
		// return ;
	display(philo, "is thinking");
}

void	*routine(void* arg)
{
	t_philo	*philo;
	int		i;
	
	philo = arg;
	i = 0;
	philo->start_time = get_time();
	if (philo->id % 2 == 0)
		usleep(100);
	while (true)
	{
		if (i >= philo->data->meals_nb && philo->data->meals_nb != -1)
			break;
		routine_eat(philo);
		routine_sleep(philo);
		routine_think(philo);
		i++;
	
	}
	return (NULL);
}