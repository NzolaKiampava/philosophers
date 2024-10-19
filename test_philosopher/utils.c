/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 10:36:12 by nkiampav          #+#    #+#             */
/*   Updated: 2024/10/19 10:36:14 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long current_time(void)
{
    struct timeval  tv;
    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void custom_sleep(long long time_in_ms)
{
    long long start = current_time();
    while (current_time() - start < time_in_ms)
        usleep(100);
}

void cleanup(t_data *data)
{
    for (int i = 0; i < data->number_of_philosophers; i++)
        pthread_mutex_destroy(&data->forks[i]);
    pthread_mutex_destroy(&data->print_mutex);
    pthread_mutex_destroy(&data->death_mutex);
    free(data->forks);
    free(data->philosophers);
}
