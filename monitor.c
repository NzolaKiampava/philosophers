/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 08:57:31 by nkiampav          #+#    #+#             */
/*   Updated: 2024/11/07 08:12:00 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_if_all_ate(t_data *data)
{
    int i;

    if (data->must_eat_count < 0)
        return (0);
    for (i = 0; i < data->num_philosophers; i++)
        if (data->philosophers[i].meals_eaten < data->must_eat_count)
            return (0);
    return (1);
}

void *death_monitor(void *arg)
{
    t_data *data = (t_data *)arg;
    int i;
    long long current_time;

    while (!check_if_all_ate(data))
    {
        i = 0;
        while (i < data->num_philosophers)
        {
            current_time = get_time();
            pthread_mutex_lock(&data->write_lock);
            if (!data->someone_died &&
                current_time - data->philosophers[i].last_meal_time > data->time_to_die)
            {
                printf("%lld %d died\n", get_time() - data->start_time, i + 1);
                data->someone_died = 1;
                pthread_mutex_unlock(&data->write_lock);
                return (NULL);
            }
            pthread_mutex_unlock(&data->write_lock);
            i++;
        }
        if (data->someone_died)
            break;
        usleep(1000);
    }
    return (NULL);
}
