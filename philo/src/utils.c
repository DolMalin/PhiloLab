/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandric <aandric@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 16:28:10 by pdal-mol          #+#    #+#             */
/*   Updated: 2022/09/21 10:15:38 by aandric          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

t_bool	check_end_program(t_philo *philo)
{
	t_bool output;
	
	output = false;
	pthread_mutex_lock(&philo->data->rw_perm);
	if (philo->data->end_program)
		output = true;
	pthread_mutex_unlock(&philo->data->rw_perm);
	return (output);
}

size_t	ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	if (!str)
		return (i);
	while (str[i])
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int					i;
	int					sign;
	unsigned long long	result;

	i = 0;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	sign = (str[i] == '-') * -1 + (str[i] != '-') * 1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		if (sign == 1 && result > INT32_MAX)
			return (0);
		if (result > (unsigned long long)INT32_MAX + 1)
			return (0);
		i++;
	}
	return ((int)(result * sign));
}

int	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(unsigned int time, t_philo *philo)
{
	unsigned int	start;

	start = get_time();
	while (get_time() - start < time)
	{
		if (check_end_program(philo))
			return ;
		usleep(1);
	}
}