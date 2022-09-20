/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdal-mol <dolmalinn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:38:56 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/09/20 12:08:54 by pdal-mol         ###   ########.fr       */
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
	if (check_end_program(philo))
		return ;
	pthread_mutex_lock(philo->fork_l);
	display(philo, "has taken a fork");
	pthread_mutex_lock(philo->fork_r);
	display(philo, "has taken a fork");
	display(philo, "is eating");
	
	pthread_mutex_lock(&philo->data->rw_perm);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->data->rw_perm);
	
	ft_usleep(philo->data->time_to_eat, philo);
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
}

void	routine_sleep(t_philo *philo)
{
	if (check_end_program(philo))
		return ;
	display(philo, "is sleeping");

	ft_usleep(philo->data->time_to_sleep, philo);
}

void	routine_think(t_philo *philo)
{
	if (check_end_program(philo))
		return ;
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
		ft_usleep(2, philo);
	while (true)
	{
		if (i >= philo->data->meals_nb && philo->data->meals_nb != -1)
			break;
		if (check_end_program(philo))
			break ;
		routine_eat(philo);
		routine_sleep(philo);
		routine_think(philo);
		i++;	
	}
	return (NULL);
}