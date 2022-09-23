/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdal-mol <dolmalinn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 16:03:44 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/09/23 15:55:42 by pdal-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

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
		data_free(data);
		free(data);
		return (0);
	}
	while (!philo_is_dead(data) && !all_meals_done(data))
		;
	philo_join_all(data->philo_array);
	data_free(data);
	return (0);
}
