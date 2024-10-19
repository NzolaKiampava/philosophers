/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 10:35:17 by nkiampav          #+#    #+#             */
/*   Updated: 2024/10/19 10:35:20 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_philosopher
{
    int             id;
    int             left_fork;
    int             right_fork;
    long long       last_meal_time;
    int             meals_eaten;
    pthread_t       thread;
    struct s_data   *data;
}               t_philosopher;

typedef struct s_data
{
    int             number_of_philosophers;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             meals_required;
    long long       start_time;
    int             all_alive;
    pthread_mutex_t *forks;
    pthread_mutex_t print_mutex;
    t_philosopher   *philosophers;
    pthread_mutex_t death_mutex;
}               t_data;

// Function Prototypes
int     init_data(t_data *data, int argc, char **argv);
void    *philosopher_routine(void *arg);
void    *monitor_routine(void *arg);
void    cleanup(t_data *data);
long long current_time(void);
void    custom_sleep(long long time_in_ms);
#endif
