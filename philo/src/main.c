/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 16:03:44 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/09/16 14:03:29 by aandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

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

void	*philo_routine(void* arg)
{
	t_philo	*philo;
	philo = arg;

	printf("%d\n", philo->id);
	return (NULL);
}

t_philo	*philo_create(int philo_id)
{
	t_philo *philo;
	
	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = philo_id;
	pthread_create(&philo->thread, NULL, &philo_routine, philo);
	pthread_join(philo->thread, NULL);
	// TODO free philo
	return (philo);
}

t_philo **philo_create_array(int	philo_nb)
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

t_data	*init_data(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->philo_nb = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->meals_nb = ft_atoi(av[5]);
	return (data);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (!check_input(ac, av))
		return (0);
	data = init_data(ac, av);
	if (!data)
		return (0);
	data->philo_array = philo_create_array(data->philo_nb);
	philo_free(data->philo_array, data->philo_nb);
	free(data);
	return (0);
}