/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:08:39 by nkiampav          #+#    #+#             */
/*   Updated: 2024/11/02 12:58:46 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void print_action(t_data *data, int id, const char *action)
{
    struct  timeval tv;
    gettimeofday(&tv, NULL);

    long long   timestamp_ms = (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000);
    long long   timestamp_us = tv.tv_usec;

    pthread_mutex_lock(&data->print_mutex);
    printf("%lld.%03lld [%d] %s\n", timestamp_ms, timestamp_us % 1000, id, action);
    pthread_mutex_unlock(&data->print_mutex);
}

static int check_death(t_data *data)
{
    pthread_mutex_lock(&data->death_mutex);
    int alive = data->all_alive;
    pthread_mutex_unlock(&data->death_mutex);
    return alive;
}

static void take_forks(t_philosopher *philo, t_data *data)
{
    pthread_mutex_lock(&data->forks[philo->left_fork]);
    pthread_mutex_lock(&data->forks[philo->right_fork]);
}

static void eat(t_philosopher *philo, t_data *data)
{
    print_action(data, philo->id, STR_FORK);
    print_action(data, philo->id, STR_EAT);
    philo->last_meal_time = current_time();
    custom_sleep(data->time_to_eat);
}

static void sleep_and_think(t_philosopher *philo, t_data *data)
{
    print_action(data, philo->id, STR_SLEEP);
    custom_sleep(data->time_to_sleep);
    print_action(data, philo->id, STR_THINK);
}

void *philosopher_routine(void *arg)
{
    t_philosopher *philo = (t_philosopher *)arg;
    t_data *data = philo->data;

    while (1)
    {
        // Check if the simulation should stop
        if (!check_death(data))
            break;

        // Try to take forks
        take_forks(philo, data);

        // Check again for death after taking forks
        if (!check_death(data))
        {
            pthread_mutex_unlock(&data->forks[philo->right_fork]);
            pthread_mutex_unlock(&data->forks[philo->left_fork]);
            break;
        }

        // Eat
        eat(philo, data);
        
        // Release the forks
        pthread_mutex_unlock(&data->forks[philo->right_fork]);
        pthread_mutex_unlock(&data->forks[philo->left_fork]);

        // Check for death before sleeping
        if (!check_death(data))
            break;

        // Sleep and think
        sleep_and_think(philo, data);
    }
    return NULL;
}
