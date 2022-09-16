/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:06:38 by aandric           #+#    #+#             */
/*   Updated: 2022/09/16 14:10:44 by aandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

static t_philo	*philo_create(int philo_id)
{
	t_philo *philo;
	
	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = philo_id;
	pthread_create(&philo->thread, NULL, &philo_routine, philo);
	pthread_join(philo->thread, NULL);
	return (philo);
}

t_philo **philo_create_array(int philo_nb)
{
	t_philo	**philo_array;
	int	i;

	philo_array = malloc(sizeof(t_philo) * philo_nb);
	if (!philo_array)
		return (NULL);
	i = 0;
	while (i < philo_nb)
	{
		philo_array[i] = philo_create(i + 1);
		i++;
	}
	return(philo_array);
}

void	*philo_routine(void* arg)
{
	t_philo	*philo;
	philo = arg;

	printf("%d\n", philo->id);
	return (NULL);
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
