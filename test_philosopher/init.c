/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 10:43:26 by nkiampav          #+#    #+#             */
/*   Updated: 2024/11/01 08:50:23 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_data(t_data *data, int argc, char **argv)
{
    data->number_of_philosophers = atoi(argv[1]);
    data->time_to_die = atoi(argv[2]);
    data->time_to_eat = atoi(argv[3]);
    data->time_to_sleep = atoi(argv[4]);
    data->meals_required = (argc == 6) ? atoi(argv[5]) : -1;
    data->all_alive = 1;

    // Initialize mutexes and allocate memory
    data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philosophers);
    if (!data->forks)
        return (1);  // Handle memory allocation failure

    for (int i = 0; i < data->number_of_philosophers; i++)
    {
        if (pthread_mutex_init(&data->forks[i], NULL) != 0)
        {
            printf("Error: Failed to initialize mutex for fork %d\n", i);
            return (1);
        }
    }

    // Initialize the print mutex
    if (pthread_mutex_init(&data->print_mutex, NULL) != 0 || pthread_mutex_init(&data->death_mutex, NULL))
    {
        printf("Error: Failed to initialize mutex\n");
        return (1);
    }

    // Allocate memory for philosophers
    data->philosophers = malloc(sizeof(t_philosopher) * data->number_of_philosophers);
    if (!data->philosophers)
    {
        free(data->forks);
        return (1);
    }

    // Initialize philosopher data
    for (int i = 0; i < data->number_of_philosophers; i++)
    {
        data->philosophers[i].id = i + 1;
        data->philosophers[i].left_fork = i;
        data->philosophers[i].right_fork = (i + 1) % data->number_of_philosophers;
        data->philosophers[i].last_meal_time = current_time();  // Initialize with current time
        data->philosophers[i].meals_eaten = 0;
        data->philosophers[i].data = data;
    }

    data->start_time = current_time();
    return (0);
}
