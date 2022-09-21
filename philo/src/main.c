/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 16:03:44 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/09/21 15:52:20 by aandric          ###   ########lyon.fr   */
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
	// for (int i = 0; i < data->philo_nb; i++)
	// {
	// 	printf("PHILO #%d\n", i);
	// 	printf("\tFORK L: %p\n", data->philo_array[i]->fork_l);
	// 	printf("\tFORK R: %p\n", data->philo_array[i]->fork_r);	
	// }	
}
/* ================================================= */

/*t_bool	philo_is_dead(t_data *data)
{
	int i ;
	int last_meal;
	int	time;

	i = 0;
	last_meal = 0;
	time = get_time();
	while (i < data->philo_nb)
	{
		pthread_mutex_lock(&data->philo_array[i]->last_meal_perm);
		last_meal = data->philo_array[i]->last_meal; 
		if (time - last_meal> data->time_to_die)
		{
			pthread_mutex_unlock(&data->philo_array[i]->last_meal_perm);
			pthread_mutex_lock(&data->end_program_perm);
			data->end_program = true;
			pthread_mutex_unlock(&data->end_program_perm);
			printf("philo %d died at %d\n", i + 1, get_time() - data->philo_array[i]->start_time);
			pthread_mutex_unlock(&data->philo_array[i]->last_meal_perm);
			return (true);
		}
		pthread_mutex_unlock(&data->philo_array[i]->last_meal_perm);
		i++;
	}
	return (false);
}*/

t_bool	philo_is_dead(t_data *data)
{
	int	i;
	int current_time;

	i = 0;
	while (i < data->philo_nb)
	{
		current_time = get_time() - data->time_zero;
		pthread_mutex_lock(&data->philo_array[i]->last_meal_perm);
		if (current_time - data->philo_array[i]->last_meal > data->time_to_die)
		{
			printf("%d %d died\n", get_time() - data->time_zero, i + 1);
			pthread_mutex_lock(&data->end_program_perm);
			data->end_program = true;
			pthread_mutex_unlock(&data->end_program_perm);
			pthread_mutex_unlock(&data->philo_array[i]->last_meal_perm);
			return (true);
		}
		pthread_mutex_unlock(&data->philo_array[i]->last_meal_perm);
		i++;
	}
	return (false);
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
	while(!philo_is_dead(data))
		;
	philo_join_all(data->philo_array);
	data_free(data);
	return (0);
}
