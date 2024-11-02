/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:54:38 by nkiampav          #+#    #+#             */
/*   Updated: 2024/11/02 16:07:49 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_threads(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->number_of_philosophers)
	{
		if (pthread_create(
				&data->philosophers[i].thread,
				NULL,
				philosopher_routine,
				&data->philosophers[i]) != 0)
		{
			printf("Error: Failed to create thread %d\n", i + 1);
			return (1);
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	monitor_thread;
	int			i;

	if ((argc != 5 && argc != 6) || init_data(&data, argc, argv) != 0)
	{
		printf("Error: Invalid arguments or failed initialization\n");
		return (1);
	}
	if (create_threads(&data) != 0 || pthread_create(
			&monitor_thread,
			NULL,
			monitor_routine,
			&data) != 0)
	{
		cleanup(&data);
		return (1);
	}
	pthread_join(monitor_thread, NULL);
	i = -1;
	while (++i < data.number_of_philosophers)
		pthread_join(data.philosophers[i].thread, NULL);
	cleanup(&data);
	return (0);
}
