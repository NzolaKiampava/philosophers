/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 10:35:40 by nkiampav          #+#    #+#             */
/*   Updated: 2024/10/19 10:35:41 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
    t_data  data;
    pthread_t monitor_thread;

    // Validate the number of arguments (5 or 6 expected)
    if (argc != 5 && argc != 6)
    {
        printf("Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep [meals_required]\n", argv[0]);
        return (1);
    }

    // Initialize the data (philosophers, forks, and mutexes)
    if (init_data(&data, argc, argv) != 0)
    {
        printf("Error: Failed to initialize data\n");
        return (1);
    }

    // Create a thread for each philosopher
    for (int i = 0; i < data.number_of_philosophers; i++)
    {
        if (pthread_create(&data.philosophers[i].thread, NULL, philosopher_routine, (void *)&data.philosophers[i]) != 0)
        {
            printf("Error: Failed to create thread for philosopher %d\n", i + 1);
            cleanup(&data);
            return (1);
        }
    }

    // Create a monitor thread to check if any philosopher dies
    if (pthread_create(&monitor_thread, NULL, monitor_routine, (void *)&data) != 0)
    {
        printf("Error: Failed to create monitor thread\n");
        cleanup(&data);
        return (1);
    }

    // Wait for all philosopher threads to finish
    for (int i = 0; i < data.number_of_philosophers; i++)
    {
        if (pthread_join(data.philosophers[i].thread, NULL) != 0)
        {
            printf("Error: Failed to join thread for philosopher %d\n", i + 1);
            cleanup(&data);
            return (1);
        }
    }

    // Wait for the monitor thread to finish
    if (pthread_join(monitor_thread, NULL) != 0)
    {
        printf("Error: Failed to join monitor thread\n");
        cleanup(&data);
        return (1);
    }

    // Cleanup all allocated resources (mutexes and memory)
    cleanup(&data);

    return (0);
}
