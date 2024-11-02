/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:08:39 by nkiampav          #+#    #+#             */
/*   Updated: 2024/11/02 12:58:46 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_forks(t_philosopher *philo, t_data *data)
{
	pthread_mutex_lock(&data->forks[philo->left_fork]);
	pthread_mutex_lock(&data->forks[philo->right_fork]);
}

static void	eat(t_philosopher *philo, t_data *data)
{
	print_action(data, philo->id, STR_FORK);
	print_action(data, philo->id, STR_EAT);
	philo->last_meal_time = current_time();
	custom_sleep(data->time_to_eat);
}

static void	sleep_and_think(t_philosopher *philo, t_data *data)
{
	print_action(data, philo->id, STR_SLEEP);
	custom_sleep(data->time_to_sleep);
	print_action(data, philo->id, STR_THINK);
}

void	*philosopher_routine(void *arg)
{
	t_data			*data;
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	data = philo->data;
	while (1)
	{
		if (!check_death(data))
			break ;
		take_forks(philo, data);
		if (!check_death(data))
		{
			pthread_mutex_unlock(&data->forks[philo->right_fork]);
			pthread_mutex_unlock(&data->forks[philo->left_fork]);
			break ;
		}
		eat(philo, data);
		pthread_mutex_unlock(&data->forks[philo->right_fork]);
		pthread_mutex_unlock(&data->forks[philo->left_fork]);
		if (!check_death(data))
			break ;
		sleep_and_think(philo, data);
	}
	return (NULL);
}
