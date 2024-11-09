/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 16:39:21 by nkiampav          #+#    #+#             */
/*   Updated: 2024/11/02 16:39:25 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_death_status(t_data *data)
{
	pthread_mutex_lock(&data->write_lock);
	if (data->someone_died)
	{
		pthread_mutex_unlock(&data->write_lock);
		return (1);
	}
	pthread_mutex_unlock(&data->write_lock);
	return (0);
}

void	philo_eat(t_philosopher *philo)
{
	t_data	*data;

	data = philo->data;
	if (check_death_status(data))
		return ;
	pthread_mutex_lock(&data->forks[philo->left_fork]);
	print_status(data, philo->id, STR_FORK);
	if (data->num_philosophers == 1)
	{
		pthread_mutex_unlock(&data->forks[philo->left_fork]);
		smart_sleep(data->time_to_die * 2);
		return ;
	}
	pthread_mutex_lock(&data->forks[philo->right_fork]);
	print_status(data, philo->id, STR_FORK);
	print_status(data, philo->id, STR_EAT);
	philo->last_meal_time = get_time();
	smart_sleep(data->time_to_eat);
	philo->meals_eaten++;
	pthread_mutex_unlock(&data->forks[philo->right_fork]);
	pthread_mutex_unlock(&data->forks[philo->left_fork]);
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;
	t_data			*data;

	philo = (t_philosopher *)arg;
	data = philo->data;
	if (philo->id % 2)
		usleep(data->time_to_eat * 500);
	while (1)
	{
		pthread_mutex_lock(&data->write_lock);
		if (data->someone_died
			|| (data->must_eat_count > 0
				&& philo->meals_eaten >= data->must_eat_count))
		{
			pthread_mutex_unlock(&data->write_lock);
			break ;
		}
		pthread_mutex_unlock(&data->write_lock);
		philo_eat(philo);
		print_status(data, philo->id, STR_SLEEP);
		smart_sleep(data->time_to_sleep);
		print_status(data, philo->id, STR_THINK);
	}
	return (NULL);
}
