/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdal-mol <dolmalinn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:06:38 by aandric           #+#    #+#             */
/*   Updated: 2022/09/16 17:27:28 by pdal-mol         ###   ########.fr       */
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
	philo->fork_l = &data->forks_array[philo->id - 1];
	philo->fork_r = &data->forks_array[philo->id % data->philo_nb];
	philo->write_perm = &data->write_perm;
	philo->data = data;
	pthread_create(&philo->thread, NULL, &routine, philo);
	pthread_join(philo->thread, NULL);
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
