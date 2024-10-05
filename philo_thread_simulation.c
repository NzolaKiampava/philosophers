/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread_simulation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:15:48 by nkiampav          #+#    #+#             */
/*   Updated: 2024/10/05 12:48:14 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_action(t_philosopher *philo, char *action, t_data *data)
{
	struct	timeval tv;
	gettimeofday(&tv, NULL);

	long long	timestamp_ms = (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000);
	long long	timestamp_us = tv.tv_usec;

	//timestamp = get_time_in_ms() - data->start_time;
	pthread_mutex_lock(&data->print_mutex);
	printf("%lld.%03lld %d %s\n", timestamp_ms, timestamp_us % 1000, philo->id, action);
	pthread_mutex_unlock(&data->print_mutex);
}

void	eat(t_philosopher *philo, t_data *data)
{
    if (philo->id % 2 == 0)
        usleep(1000); // Optional small delay for odd philosophers

    pthread_mutex_lock(philo->left_fork);
    print_action(philo, STR_FORK, data);
    pthread_mutex_lock(philo->right_fork);
    print_action(philo, STR_FORK, data);

    philo->last_meal_time = get_time_in_ms();
    usleep(1000); // Short delay before starting to eat to differentiate timestamps
    print_action(philo, STR_EAT, data);
    usleep(data->time_to_eat * 1000);
    philo->meals_eaten++;

    pthread_mutex_unlock(philo->right_fork);
    pthread_mutex_unlock(philo->left_fork);
}

void	sleep_and_think(t_philosopher *philo, t_data *data)
{
	print_action(philo, STR_SLEEP, data);
	usleep(data->time_to_sleep * 1000 + (rand() % 100));
	print_action(philo, STR_THINK, data);
	usleep(100 + (rand() % 100));
}

void	start_simulation(t_data *data)
{
    int i;

    data->start_time = get_time_in_ms();
    
    // Create philosopher threads
    i = -1;
    while (++i < data->num_philo)
    {
    	data->philo[i].last_meal_time = data->start_time;
        pthread_create(&data->philo[i].thread, NULL, philo_routine, &data->philo[i]);
    }

    // Monitor for deaths
    if (check_death(data)) 
    {
    	i = -1;
    	while (++i < data->num_philo)
    		pthread_detach(data->philo[i].thread);
        return;
    }

    i = -1;
    while (++i < data->num_philo)
    	pthread_join(data->philo[i].thread, NULL);
}
