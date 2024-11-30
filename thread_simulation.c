/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_simulation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <nkiampav@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-23 20:00:14 by nkiampav          #+#    #+#             */
/*   Updated: 2024/11/30 14:17:57 by nkiampav         ###   ########.fr       */
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

int	lock_forks_left_first(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	if (check_if_simulation_finished(philo->data))
	{
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
		return (1);
	}
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	return (0);
}

int	lock_forks_right_first(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	if (check_if_simulation_finished(philo->data))
	{
		pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
		return (1);
	}
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	return (0);
}
