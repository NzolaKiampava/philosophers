/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:04:15 by nkiampav          #+#    #+#             */
/*   Updated: 2024/09/30 13:07:36 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000LL + tv.tv_usec / 1000);
}

int	check_death(t_data *data)
{
    int i;
    struct timeval tv; // Use struct timeval to get microsecond precision

    while (1) {
        i = -1;  // Reset the counter
        while (++i < data->num_philo) {
            // Get the current time with microsecond precision
            gettimeofday(&tv, NULL);
            long long cur_time_ms = (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000); // in milliseconds
            long long cur_time_us = tv.tv_usec; // in microseconds

            // Check if the philosopher has exceeded their time to die
            if (cur_time_ms - data->philo[i].last_meal_time > data->time_to_die) {
                pthread_mutex_lock(&data->print_mutex);  // Lock for printing
                // Print the philosopher id and timestamp with microsecond detail
                printf("%lld.%03lld %d \033[31m died\n\033[0m", cur_time_ms, cur_time_us % 1000, data->philo[i].id);
                pthread_mutex_unlock(&data->print_mutex);
                return (1);  // Philosopher died, stop the simulation
            }
        }
        usleep(1000);  // Sleep for 1 ms between checks
    }
    return (0);
}
