/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_simulation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <nkiampav@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-23 20:00:14 by nkiampav          #+#    #+#             */
/*   Updated: 2024-11-23 20:00:14 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_if_simulation_finished(t_data *data)
{
	int	result;

	pthread_mutex_lock(&data->death_mutex);
	result = data->someone_died;
	pthread_mutex_unlock(&data->death_mutex);
	return (result);
}

void	set_simulation_stopped(t_data *data)
{
	pthread_mutex_lock(&data->death_mutex);
	data->someone_died = 1;
	pthread_mutex_unlock(&data->death_mutex);
}
