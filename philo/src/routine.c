/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdal-mol <dolmalinn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:38:56 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/09/16 17:37:28 by pdal-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	display(t_philo *philo, const char *str)
{
	pthread_mutex_lock(philo->write_perm);
	printf("timestamp %d %s\n", philo->id, str);
	pthread_mutex_unlock(philo->write_perm);
}

void	routine_eat(t_philo *philo)
{
	// MUST TAKE A FORK
	pthread_mutex_lock(philo->fork_l);
	display(philo, "has taken a fork");
	pthread_mutex_lock(philo->fork_r);
	display(philo, "has taken a fork");
	display(philo, "is eating");
	// SLEEP * time_to_eat
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
}

void	routine_sleep(t_philo *philo)
{
	display(philo, "is sleeping");
	// SLEEP * time_to_sleep
}

void	routine_think(t_philo *philo)
{
	display(philo, "is thinking");
}

void	*routine(void* arg)
{
	t_philo	*philo;
	int		i;
	
	philo = arg;
	i = 0;
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