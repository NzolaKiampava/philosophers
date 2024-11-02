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

int	validate_arguments(int argc, char **argv)
{
	int	i;
	
	i = 1;
	while (i < argc) {
		if (!ft_is_number(argv[i])) 
		{
		    printf("Error: Arg %d ('%s') is not valid\n", i, argv[i]);
		    return 1;
		}
		i++;
	}
	return 0;
}

int	allocate_resources(t_data *data)
{
	data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philosophers);
	if (!data->forks) 
	{
		printf("Error: Failed to allocate memory for forks\n");
		return 1;
	}

	data->philosophers = malloc(sizeof(t_philosopher) * data->number_of_philosophers);
	if (!data->philosophers) 
	{
		printf("Error: Failed to allocate memory for philosophers\n");
		free(data->forks);
		return 1;
	}

	return 0;
}

static int initialize_mutexes(t_data *data)
{
    int i = 0;
    while (i < data->number_of_philosophers) {
        if (pthread_mutex_init(&data->forks[i], NULL) != 0) {
            printf("Error: Failed to initialize mutex for fork %d\n", i);
            return 1;
        }
        i++;
    }

    if (pthread_mutex_init(&data->print_mutex, NULL) != 0 || 
        pthread_mutex_init(&data->death_mutex, NULL) != 0) {
        printf("Error: Failed to initialize print or death mutex\n");
        return 1;
    }

    return 0;
}

static int initialize_philosophers(t_data *data)
{
    int i = 0;
    while (i < data->number_of_philosophers) {
        data->philosophers[i].id = i + 1;
        data->philosophers[i].left_fork = i;
        data->philosophers[i].right_fork = (i + 1) % data->number_of_philosophers;
        data->philosophers[i].last_meal_time = current_time();
        data->philosophers[i].meals_eaten = 0;
        data->philosophers[i].data = data;
        i++;
    }
    return 0;
}

int init_data(t_data *data, int argc, char **argv)
{
    // Step 1: Validate Arguments
    if (validate_arguments(argc, argv) != 0)
        return 1;

    // Step 2: Parse Arguments
    data->number_of_philosophers = ft_atoi(argv[1]);
    data->time_to_die = ft_atoi(argv[2]);
    data->time_to_eat = ft_atoi(argv[3]);
    data->time_to_sleep = ft_atoi(argv[4]);
    data->meals_required = (argc == 6) ? ft_atoi(argv[5]) : -1;
    data->all_alive = 1;

    // Step 3: Allocate Resources
    if (allocate_resources(data) != 0)
        return 1;

    // Step 4: Initialize Mutexes
    if (initialize_mutexes(data) != 0)
        return 1;

    // Step 5: Initialize Philosophers
    if (initialize_philosophers(data) != 0)
        return 1;

    data->start_time = current_time();
    return 0;
}
