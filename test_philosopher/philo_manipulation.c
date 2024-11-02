/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_manipulation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 16:39:21 by nkiampav          #+#    #+#             */
/*   Updated: 2024/11/02 16:39:25 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_data *data, int id, const char *action)
{
	struct timeval	tv;
	long long		timestamp_ms;
	long long		timestamp_us;

	timestamp_ms = (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000);
	timestamp_us = tv.tv_usec % 1000;
	gettimeofday(&tv, NULL);
	pthread_mutex_lock(&data->print_mutex);
	printf("%lld.%03lld [%d] %s\n", timestamp_ms, timestamp_us, id, action);
	pthread_mutex_unlock(&data->print_mutex);
}

int	check_death(t_data *data)
{
	int	alive;

	alive = data->all_alive;
	pthread_mutex_lock(&data->death_mutex);
	pthread_mutex_unlock(&data->death_mutex);
	return (alive);
}

void	cleanup(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->number_of_philosophers)
		pthread_mutex_destroy(&data->forks[i]);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	free(data->forks);
	free(data->philosophers);
}
