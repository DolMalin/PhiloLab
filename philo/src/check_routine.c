/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdal-mol <dolmalinn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 15:51:32 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/09/23 15:55:59 by pdal-mol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

t_bool	program_stop(t_philo *philo)
{
	t_bool	output;

	output = false;
	pthread_mutex_lock(&philo->data->end_program_perm);
	if (philo->data->end_program)
		output = true;
	pthread_mutex_unlock(&philo->data->end_program_perm);
	return (output);
}

t_bool	meals_stop(t_philo *philo)
{
	t_bool	output;

	output = false;
	pthread_mutex_lock(&philo->data->end_meals_perm);
	if (philo->data->end_meals)
		output = true;
	pthread_mutex_unlock(&philo->data->end_meals_perm);
	return (output);
}

t_bool	all_meals_done(t_data *data)
{
	int	i;

	i = 0;
	if (data->meals_nb == -1)
		return (false);
	while (i < data->philo_nb)
	{
		pthread_mutex_lock(&data->philo_array[i]->meal_count_perm);
		if (data->philo_array[i]->meals_count < data->meals_nb)
		{
			pthread_mutex_unlock(&data->philo_array[i]->meal_count_perm);
			return (false);
		}
		pthread_mutex_unlock(&data->philo_array[i]->meal_count_perm);
		i++;
	}
	pthread_mutex_lock(&data->end_program_perm);
	data->end_program = true;
	pthread_mutex_unlock(&data->end_program_perm);
	return (true);
}

t_bool	philo_is_dead(t_data *data)
{
	int	i;
	int	current_time;

	i = 0;
	while (i < data->philo_nb)
	{
		current_time = get_time();
		pthread_mutex_lock(&data->philo_array[i]->last_meal_perm);
		if (current_time - data->philo_array[i]->last_meal > data->time_to_die)
		{
			pthread_mutex_lock(&data->end_program_perm);
			printf("%d %d died\n", get_time() - data->philo_array[i]->time_zero,
				i + 1);
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
