/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:38:56 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/09/21 15:47:50 by aandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"


void	display(t_philo *philo, const char *str)
{	
	int time;
	
	if (program_stop(philo))
		return ;
	time = get_time();
	// pthread_mutex_lock(&philo->data->display_perm);
	printf("%d %d %s\n", time - philo->data->time_zero, philo->id, str);
	// pthread_mutex_unlock(&philo->data->display_perm);
}

t_bool	routine_eat(t_philo *philo)
{
	int last_meal;

	if (program_stop(philo))
			return (false);
	pthread_mutex_lock(philo->fork_l);
	display(philo, "has taken a fork");
	pthread_mutex_lock(philo->fork_r);
	display(philo, "has taken a fork");
	last_meal = get_time() - philo->data->time_zero;
	display(philo, "is eating");
	pthread_mutex_lock(&philo->last_meal_perm);
	philo->last_meal = last_meal;
	pthread_mutex_unlock(&philo->last_meal_perm);
	ft_usleep(philo->data->time_to_eat, philo);
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
	return (true);
}

t_bool	routine_sleep(t_philo *philo)
{
	if (program_stop(philo))
			return (false);
	display(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep, philo);
	return (true);
}

t_bool	routine_think(t_philo *philo)
{
	if (program_stop(philo))
			return (false);
	display(philo, "is thinking");
	return (true);
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
		if (!routine_eat(philo))
			return (NULL);
		if (!routine_sleep(philo))
			return (NULL);
		if (!routine_think(philo))
			return (NULL);
		i++;
	
	}
	return (NULL);
}