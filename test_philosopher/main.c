/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:54:38 by nkiampav          #+#    #+#             */
/*   Updated: 2024/11/02 09:42:50 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
    t_data data;
    pthread_t monitor_thread;

    if (argc != 5 && argc != 6)
    {
        printf(STR_USAGE, argv[0]);
        return (1);
    }

    if (init_data(&data, argc, argv) != 0)
    {
        printf("Error: Failed to initialize data\n");
        return (1);
    }

    for (int i = 0; i < data.number_of_philosophers; i++)
    {
        if (pthread_create(&data.philosophers[i].thread, NULL, philosopher_routine, (void *)&data.philosophers[i]) != 0)
        {
            printf("Error: Failed to create thread for philosopher %d\n", i + 1);
            cleanup(&data);
            return (1);
        }
    }

    if (pthread_create(&monitor_thread, NULL, monitor_routine, (void *)&data) != 0)
    {
        printf("Error: Failed to create monitor thread\n");
        cleanup(&data);
        return (1);
    }

    pthread_join(monitor_thread, NULL);

    for (int i = 0; i < data.number_of_philosophers; i++)
        pthread_join(data.philosophers[i].thread, NULL);

    cleanup(&data);
    return (0);
}
