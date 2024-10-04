/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:08:39 by nkiampav          #+#    #+#             */
/*   Updated: 2024/09/30 13:50:50 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philosopher	*philo;
	t_data			*data;

	philo = (t_philosopher *)arg;
	data = (t_data *)philo->data;
	while (1)
	{
		eat(philo, data);
		sleep_and_think(philo, data);

		if (data->must_eat_count != -1 && philo->meals_eaten >= data->must_eat_count)
			break ;
		/*
		if (data->must_eat_count != -1)
		{
			if (philo->meals_eaten >= data->must_eat_count)
				break ;
		}
		*/
	}
	return (NULL);
}

void	init_philo(t_data *data)
{
	int			i;
	//double		id_fork;
	//pthread_t	t_id;

	i = -1;
	data->philo = malloc(sizeof(t_philosopher) * data->num_philo);
	if (!data->philo)
	{
		printf("Error: Failed to allocate memory fo philosophers\n");
		exit(1);
	}
	while (++i < data->num_philo)
	{
		//id_fork = (i + 1) % data->num_philo;
		//t_id = &data->philo[i].thread;
		data->philo[i].id = i + 1;
		data->philo[i].left_fork = &data->forks[i];
		data->philo[i].right_fork = &data->forks[(i + 1) % data->num_philo];
		data->philo[i].time_to_die = data->time_to_die;
		data->philo[i].time_to_eat = data->time_to_eat;
		data->philo[i].time_to_sleep = data->time_to_sleep;
		data->philo[i].must_eat_count = data->must_eat_count;
		data->philo[i].meals_eaten = 0;
		data->philo[i].data = data;
		if (pthread_create(&data->philo[i].thread, NULL, philo_routine, &data->philo[i]) != 0)
		{
			printf("Error: Failed to create thread for philosopher %d\n", i + 1);
			exit(1);
		}
	}
}

void	init_mutexes(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philo);
	if (!data->forks)
	{
		printf("Error allocating memory for forks\n");
		exit(1);
	}
	i = -1;
	while (++i < data->num_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			printf("Error initializing mutex for fork %d\n", i);
			exit(1);
		}
	}
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
	{
		printf("Error initializing print mutex\n");
		exit(1);
	}
}

void	destroy_mutexes(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_philo)
		pthread_mutex_destroy(&data->forks[i]);
	pthread_mutex_destroy(&data->print_mutex);
}
