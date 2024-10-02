/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread_simulation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:15:48 by nkiampav          #+#    #+#             */
/*   Updated: 2024/09/30 14:41:35 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_action(t_philosopher *philo, char *action, t_data *data)
{
	long long	timestamp;

	timestamp = get_time_in_ms() - data->start_time;
	pthread_mutex_lock(&data->print_mutex);
	printf("%lld %d %s\n", timestamp, philo->id, action);
	pthread_mutex_unlock(&data->print_mutex);
}

void	eat(t_philosopher *philo, t_data *data)
{
	pthread_mutex_lock(philo->left_fork);
	print_action(philo, "has taken a fork", data);
	pthread_mutex_lock(philo->right_fork);
	print_action(philo, "has taken a fork", data);
	philo->last_meal_time = get_time_in_ms();
	print_action(philo, "is eating", data);
	usleep(data->time_to_eat * 1000);
	philo->meal_eaten++;
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	sleep_and_think(t_philosopher *philo, t_data *data)
{
	print_action(philo, "is sleeping", data);
	usleep(data->time_to_sleep * 1000);
	print_action(philo, "is thinking", data);
}

void	start_simulation(t_data *data)
{
	int			i;
	pthread_t		t_id;

	data->start_time = get_time_in_ms();
	i = -1;
	while (++i < data->num_philo)
	{
		t_id = &data->philo[i].thread;
		data->philo[i].last_meal_time = data->start_time;
		pthread_create(t_id, NULL, philo_routine, &data->philo[i]);
	}

	i = -1;
	if (check_death(data))
	{
		while (++i < data->num_philo)
			pthread_detach(data->philo[i].thread);
		return ;
	}

	i = -1;
	while (++i < data->num_philo)
		pthread_join(data->philo[i].thread, NULL);
}
