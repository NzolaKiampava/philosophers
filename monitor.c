/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 08:57:31 by nkiampav          #+#    #+#             */
/*   Updated: 2024/11/07 08:12:00 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_death(t_data *data, t_philosopher *philo)
{
	long long	c_time;
	long long	last_meal;

	c_time = get_time();
	pthread_mutex_lock(&data->meal_mutex);
	last_meal = philo->last_meal_time;
	pthread_mutex_unlock(&data->meal_mutex);
	if (c_time - last_meal > data->time_to_die)
	{
		if (!check_if_simulation_finished(data))
		{
			pthread_mutex_lock(&data->print_mutex);
			printf("%lld %d died\n", c_time - data->start_time, philo->id);
			set_simulation_stopped(data);
			pthread_mutex_unlock(&data->print_mutex);
		}
		return (1);
	}
	return (0);
}

static int	check_meals(t_data *data)
{
	int	i;
	int	finished;

	if (data->must_eat_count == -1)
		return (0);
	finished = 1;
	i = -1;
	pthread_mutex_lock(&data->meal_mutex);
	while (++i < data->num_philosophers)
	{
		if (data->philosophers[i].meals_eaten < data->must_eat_count)
		{
			finished = 0;
			break ;
		}
	}
	pthread_mutex_unlock(&data->meal_mutex);
	return (finished);
}

void	*monitor_philosophers(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (1)
	{
		i = -1;
		while (++i < data->num_philosophers)
		{
			if (check_death(data, &data->philosophers[i]))
				return (NULL);
		}
		if (check_meals(data))
		{
			set_simulation_stopped(data);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
