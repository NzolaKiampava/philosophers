/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 10:43:26 by nkiampav          #+#    #+#             */
/*   Updated: 2024/11/02 15:38:07 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutexes(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philosophers);
	if (!data->forks)
		return (1);
	if (pthread_mutex_init(&data->write_lock, NULL))
		return (1);
	i = -1;
	while (++i < data->num_philosophers)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (1);
	}
	return (0);
}

int	init_philosophers(t_data *data)
{
	int	i;

	i = -1;
	data->philosophers = malloc(sizeof(t_philosopher) * data->num_philosophers);
	if (!data->philosophers)
		return (1);
	while (++i < data->num_philosophers)
	{
		data->philosophers[i].id = i;
		data->philosophers[i].left_fork = i;
		data->philosophers[i].right_fork = (i + 1) % data->num_philosophers;
		data->philosophers[i].meals_eaten = 0;
		data->philosophers[i].last_meal_time = get_time();
		data->philosophers[i].data = data;
	}
	return (0);
}

int	init_simulation(t_data *data)
{
	int			i;
	pthread_t	monitor;

	i = -1;
	if (init_mutexes(data) || init_philosophers(data))
		return (1);
	data->start_time = get_time();
	while (++i < data->num_philosophers)
	{
		if (pthread_create(&data->philosophers[i].thread, NULL,
				philosopher_routine, &data->philosophers[i]))
			return (1);
	}
	if (pthread_create(&monitor, NULL, death_monitor, data))
		return (1);
	pthread_detach(monitor);
	return (0);
}
