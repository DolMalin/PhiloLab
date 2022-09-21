/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:38:56 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/09/21 17:46:44 by aandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"


void	display(t_philo *philo, const char *str)
{	
	int time;
	
	if (program_stop(philo))
		return ;
	time = get_time();
	printf("%d %d %s\n", time - philo->time_zero, philo->id, str);
	//printf("%d %d %s\n", time - philo->time_zero, philo->id, str);
	// pthread_mutex_lock(&philo->data->display_perm);
	// ft_putnbr_fd(time - philo->data->time_zero, 1);
	// write(1, " ", 1);
	// ft_putnbr_fd(philo->id, 1);
	// write(1, " ", 1);
	// write(1, str, ft_strlen(str));
	// write(1, "\n", 1);
	// pthread_mutex_unlock(&philo->data->display_perm);
}

t_bool	routine_eat(t_philo *philo)
{
	int last_meal;

	if (program_stop(philo))
			return (false);
	pthread_mutex_lock(&philo->data->forks_array[philo->id - 1]);
	display(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->forks_array[philo->id % philo->data->philo_nb]);
	display(philo, "has taken a fork");
	
	last_meal = get_time() - philo->time_zero;
	//last_meal = get_time() - philo->time_zero;
	
	display(philo, "is eating");
	pthread_mutex_lock(&philo->last_meal_perm);
	philo->last_meal = last_meal;
	pthread_mutex_unlock(&philo->last_meal_perm);
	
	ft_usleep(philo->data->time_to_eat, philo);
	pthread_mutex_unlock(&philo->data->forks_array[philo->id - 1]);
	pthread_mutex_unlock(&philo->data->forks_array[philo->id % philo->data->philo_nb]);
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
	philo->time_zero = get_time();
	if (philo->id % 2 == 0)
		usleep((philo->data->time_to_eat * 1000) / 4);
	while (true)
	{
		// if (i >= philo->data->meals_nb && philo->data->meals_nb != -1)
		// 	break;
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