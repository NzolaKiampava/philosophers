/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 08:57:31 by nkiampav          #+#    #+#             */
/*   Updated: 2024/11/01 10:26:45 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int has_philosopher_died(t_philosopher *philo)
{
    t_data *data = philo->data;

    pthread_mutex_lock(&data->death_mutex);

    // Calcular o tempo desde a última refeição
    long long time_since_last_meal = current_time() - philo->last_meal_time;

    if (time_since_last_meal >= data->time_to_die && data->all_alive)
    {
        // Sinalizar que um filósofo morreu e parar todos imediatamente
        data->all_alive = 0;
        
        // Imprimir a mensagem de morte
        pthread_mutex_lock(&data->print_mutex);
        printf("%lld [%d] died 🥵 \n", current_time() - data->start_time, philo->id);
        pthread_mutex_unlock(&data->print_mutex);

        pthread_mutex_unlock(&data->death_mutex);
        return 1;  // Retornar que a morte foi detectada
    }

    pthread_mutex_unlock(&data->death_mutex);
    return 0;
}

void *monitor_routine(void *arg)
{
    t_data *data = (t_data *)arg;

    while (1)
    {
        for (int i = 0; i < data->number_of_philosophers; i++)
        {
            if (has_philosopher_died(&data->philosophers[i]))
                return NULL;  // Parar o monitor imediatamente após detectar a morte
        }
        usleep(1000);  // Pausa para reduzir a carga da CPU
    }
}
