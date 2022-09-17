/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdal-mol <dolmalinn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:38:56 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/09/17 15:21:23 by pdal-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"


void	display(t_philo *philo, const char *str, int start_time)
{
	pthread_mutex_lock(&philo->data->write_perm);
	printf("%d %d %s\n", get_time() - start_time, philo->id, str);
	pthread_mutex_unlock(&philo->data->write_perm);
	usleep(20);
}

void	routine_eat(t_philo *philo, int start_time)
{
	// MUST TAKE A FORK
	pthread_mutex_lock(philo->fork_l);
	display(philo, "has taken a fork", start_time);
	pthread_mutex_lock(philo->fork_r);
	display(philo, "has taken a fork", start_time);
	display(philo, "is eating", start_time);
	
	// SLEEP * time_to_eat
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
}

void	routine_sleep(t_philo *philo, int start_time)
{
	display(philo, "is sleeping", start_time);

	ft_usleep(philo->data->time_to_sleep);
	// SLEEP * time_to_sleep
}

void	routine_think(t_philo *philo, int start_time)
{
	display(philo, "is thinking", start_time);
}

void	*routine(void* arg)
{
	t_philo	*philo;
	int		i;
	int		start_time;
	
	philo = arg;
	i = 0;
	start_time = get_time();
	if (philo->id % 2 != 0)
		ft_usleep(100);
	while (true)
	{
		if (i >= philo->data->meals_nb && philo->data->meals_nb != -1)
			break;
		routine_eat(philo, start_time);
		routine_sleep(philo, start_time);
		routine_think(philo, start_time);
		i++;	
	}
	return (NULL);
}