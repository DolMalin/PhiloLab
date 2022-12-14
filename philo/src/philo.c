/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdal-mol <dolmalinn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:06:38 by aandric           #+#    #+#             */
/*   Updated: 2022/09/23 15:44:23 by pdal-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

static t_philo	*philo_create(t_data *data, int philo_id)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = philo_id;
	philo->data = data;
	philo->meals_count = 0;
	philo->last_meal = get_time();
	pthread_mutex_init(&philo->last_meal_perm, NULL);
	pthread_mutex_init(&philo->meal_count_perm, NULL);
	pthread_create(&philo->thread, NULL, &routine, philo);
	return (philo);
}

t_philo	**philo_create_array(t_data *data)
{
	t_philo	**philo_array;
	int		i;

	philo_array = malloc(sizeof(t_philo) * data->philo_nb);
	if (!philo_array)
		return (NULL);
	i = 0;
	while (i < data->philo_nb)
	{
		philo_array[i] = philo_create(data, i + 1);
		if (!philo_array[i])
		{
			philo_free(philo_array, i - 1);
			return (NULL);
		}
		i++;
	}
	return (philo_array);
}

void	philo_join_all(t_philo **philo_array)
{
	int	i;

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
