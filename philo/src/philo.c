/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:06:38 by aandric           #+#    #+#             */
/*   Updated: 2022/09/21 15:56:59 by aandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

static t_philo	*philo_create(t_data *data, int philo_id)
{
	t_philo *philo;
	
	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = philo_id;
	// philo->fork_l = &data->forks_array[philo->id - 1];
	// philo->fork_r = &data->forks_array[philo->id % data->philo_nb];
	philo->data = data;
	philo->last_meal = get_time();
	pthread_mutex_init(&philo->last_meal_perm, NULL);
	pthread_create(&philo->thread, NULL, &routine, philo);
	return (philo);
}

/* TODO:
	secure if philo_create return null and free all thats being allocated
*/

t_philo **philo_create_array(t_data *data)
{
	t_philo	**philo_array;
	int	i;

	philo_array = malloc(sizeof(t_philo) * data->philo_nb);
	if (!philo_array)
		return (NULL);
	i = 0;
	while (i < data->philo_nb)
	{
		philo_array[i] = philo_create(data, i + 1);
		i++;
	}
	return(philo_array);
}

void	philo_join_all(t_philo **philo_array)
{
	int i;

	i = 0;
	while (philo_array[i])
	{
		pthread_join(philo_array[i]->thread, NULL);
		i++;
	}
}

void	philo_free(t_philo **philo_array, int philo_nb)
{
	int	i;

	i = 0;
	while (i < philo_nb)
	{
		free(philo_array[i]);
		i++;
	}
	free(philo_array);
}
