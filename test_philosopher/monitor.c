/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 08:57:31 by nkiampav          #+#    #+#             */
/*   Updated: 2024/11/01 10:26:45 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	has_philosopher_died(t_philosopher *philo)
{
	long long	time_since_last_meal;
	long long	time_of_death;
	t_data		*data;

	data = philo->data;
	time_since_last_meal = current_time() - philo->last_meal_time;
	time_of_death = current_time() - data->start_time;
	pthread_mutex_lock(&data->death_mutex);
	if (time_since_last_meal >= data->time_to_die && data->all_alive)
	{
		data->all_alive = 0;
		pthread_mutex_lock(&data->print_mutex);
		printf("%lld [%d] died\n", time_of_death, philo->id);
		pthread_mutex_unlock(&data->print_mutex);
		pthread_mutex_unlock(&data->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->death_mutex);
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	i = -1;
	while (1)
	{
		while (++i < data->number_of_philosophers)
		{
			if (has_philosopher_died(&data->philosophers[i]))
				return (NULL);
		}
		usleep(1000);
	}
}
