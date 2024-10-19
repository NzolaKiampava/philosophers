/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 10:35:57 by nkiampav          #+#    #+#             */
/*   Updated: 2024/10/19 10:36:03 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *philosopher_routine(void *arg)
{
    t_philosopher *philo = (t_philosopher *)arg;
    t_data *data = philo->data;

    while (1)
    {
        pthread_mutex_lock(&data->death_mutex);
        if (!data->all_alive)
        {
            pthread_mutex_unlock(&data->death_mutex);
            break;
        }
        pthread_mutex_unlock(&data->death_mutex);

        // Take forks and eat
        pthread_mutex_lock(&data->forks[philo->left_fork]);
        pthread_mutex_lock(&data->forks[philo->right_fork]);

        pthread_mutex_lock(&data->print_mutex);
        printf("%lld %d has taken a fork\n", current_time() - data->start_time, philo->id);
        printf("%lld %d is eating\n", current_time() - data->start_time, philo->id);
        pthread_mutex_unlock(&data->print_mutex);

        philo->last_meal_time = current_time();
        custom_sleep(data->time_to_eat);
        philo->meals_eaten++;

        pthread_mutex_unlock(&data->forks[philo->right_fork]);
        pthread_mutex_unlock(&data->forks[philo->left_fork]);

        // Sleep
        pthread_mutex_lock(&data->print_mutex);
        printf("%lld %d is sleeping\n", current_time() - data->start_time, philo->id);
        pthread_mutex_unlock(&data->print_mutex);
        custom_sleep(data->time_to_sleep);

        // Think
        pthread_mutex_lock(&data->print_mutex);
        printf("%lld %d is thinking\n", current_time() - data->start_time, philo->id);
        pthread_mutex_unlock(&data->print_mutex);
    }
    return (NULL);
}

void *monitor_routine(void *arg)
{
    t_data *data = (t_data *)arg;
    int i;

    while (1)
    {
        for (i = 0; i < data->number_of_philosophers; i++)
        {
            pthread_mutex_lock(&data->death_mutex);
            if (current_time() - data->philosophers[i].last_meal_time >= data->time_to_die)
            {
                pthread_mutex_lock(&data->print_mutex);
                printf("%lld %d died\n", current_time() - data->start_time, data->philosophers[i].id);
                pthread_mutex_unlock(&data->print_mutex);

                data->all_alive = 0;
                pthread_mutex_unlock(&data->death_mutex);
                return (NULL);
            }
            pthread_mutex_unlock(&data->death_mutex);
        }
        usleep(1000);
    }
}
