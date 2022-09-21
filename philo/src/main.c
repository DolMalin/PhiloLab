/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 16:03:44 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/09/21 13:29:13 by aandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

/*
TODO:

	0 in parsing
 */


/* ================================================= */
/*  DEBUG */

// void	log_forks(t_data *data)
// {
// 	printf("FORKS ID:\n");
// 	for (int i = 0; i < data->philo_nb; i++)
// 		printf("\tFORKS #%d: %p\n", i, &data->forks_array[i]);
// 	for (int i = 0; i < data->philo_nb; i++)
// 	{
// 		printf("PHILO #%d\n", i);
// 		printf("\tFORK L: %p\n", data->philo_array[i]->fork_l);
// 		printf("\tFORK R: %p\n", data->philo_array[i]->fork_r);	
// 	}	
// }
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
	// CHECK IF A PHILO IS DEAD
	while(!data->end_program)
	{
		int i = 0;
		while (i < data->philo_nb)
		{
			pthread_mutex_lock(&data->rw_perm);
			
			//if (get_time() - data->philo_array[i]->last_meal > data->time_to_die)
			if (((get_time() - data->time_zero) - data->philo_array[i]->last_meal) > data->time_to_die)
			{
				data->end_program = true;
				pthread_mutex_unlock(&data->rw_perm);
				printf("philo %d died\n", i + 1);
				break ;
			}
			pthread_mutex_unlock(&data->rw_perm);
			i++;
		}
	} 
	philo_join_all(data->philo_array);
	data_free(data);
	return (0);
}
