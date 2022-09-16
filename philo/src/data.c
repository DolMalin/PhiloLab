/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdal-mol <dolmalinn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:12:46 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/09/16 16:44:16 by pdal-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

/* 
	Decide if we wants mutex_array as * or **
*/
static pthread_mutex_t	*forks_init(int	philo_nb)
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

t_data	*data_init(int ac, char **av)
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
	pthread_mutex_init(&data->write_perm, NULL);
	return (data);
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
