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

int	check_if_all_ate(t_data *data)
{
	int	i;

	i = -1;
	if (data->must_eat_count < 0)
		return (0);
	while (++i < data->num_philosophers)
	{
		if (data->philosophers[i].meals_eaten < data->must_eat_count)
			return (0);
	}
	return (1);
}

static int	check_philosopher_death(t_data *data, int i)
{
	long long	current_time;
	long long	time_since_meal;

	current_time = get_time();
	pthread_mutex_lock(&data->write_lock);
	time_since_meal = current_time - data->philosophers[i].last_meal_time;
	if (!data->someone_died && time_since_meal > data->time_to_die)
	{
		printf("%lld %d died\n", get_time() - data->start_time, i + 1);
		data->someone_died = 1;
		pthread_mutex_unlock(&data->write_lock);
		return (1);
	}
	pthread_mutex_unlock(&data->write_lock);
	return (0);
}

void	*death_monitor(void *arg)
{
	t_data		*data;
	int			i;

	data = (t_data *)arg;
	while (!check_if_all_ate(data))
	{
		i = 0;
		while (i < data->num_philosophers)
		{
			if (check_philosopher_death(data, i))
				return (NULL);
			i++;
		}
		if (data->someone_died)
			break ;
		usleep(1000);
	}
	return (NULL);
}
