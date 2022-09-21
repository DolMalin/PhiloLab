/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 16:03:44 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/09/21 09:37:02 by aandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

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
	data_free(data);
	return (0);
}
