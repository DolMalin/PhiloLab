/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdal-mol <dolmalinn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 16:03:44 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/09/16 16:05:04 by pdal-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"


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

/* 
	Decide if we wants mutex_array as * or **
*/

pthread_mutex_t	*forks_init(int	philo_nb)
{
	int				i;
	pthread_mutex_t	*forks_array;

	i = 0;
	forks_array = malloc(sizeof(pthread_mutex_t) * philo_nb);
	if (!forks_array)
		return (NULL);
	while (i < philo_nb)
	{
		pthread_mutex_init(&forks_array[i], NULL);
		i++;
	}
	return (forks_array);
}

void	data_free(t_data *data)
{
	philo_free(data->philo_array, data->philo_nb);
	/* TODO:
		Use of mutex destroy?
	*/
	free(data->forks_array);
	free(data);
	
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
	data->forks_array = forks_init(data->philo_nb);
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
	data->philo_array = philo_create_array(data);
	log_forks(data);
	if (!data->philo_array)
	{
		free(data);
		return (0);
	}
	data_free(data);
	return (0);
}
