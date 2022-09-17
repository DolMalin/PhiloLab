/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdal-mol <dolmalinn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 16:03:44 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/09/17 15:20:21 by pdal-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

/*
TODO:

	0 in parsing
 */
/* ================================================= */
/*  DEBUG */
void	log_forks(t_data *data)
{
	printf("FORKS ID:\n");
	for (int i = 0; i < data->philo_nb; i++)
		printf("\tFORKS #%d: %p\n", i, &data->forks_array[i]);
	for (int i = 0; i < data->philo_nb; i++)
	{
		printf("PHILO #%d\n", i);
		printf("\tFORK L: %p\n", data->philo_array[i]->fork_l);
		printf("\tFORK R: %p\n", data->philo_array[i]->fork_r);	
	}	
}
/* ================================================= */


void	join_philos(t_philo **array)
{
	int i;

	i = 0;
	while (array[i])
	{
		pthread_join(array[i]->thread, NULL);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (!check_input(ac, av))
		return (0);
	data = data_init(ac, av);
	if (!data)
		return (0);
	data->philo_array = philo_create_array(data);
	if (!data->philo_array)
	{
		free(data);
		return (0);
	}
	join_philos(data->philo_array);
	data_free(data);
	return (0);
}
