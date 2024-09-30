/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:59:57 by nkiampav          #+#    #+#             */
/*   Updated: 2024/09/30 12:07:10 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philosopher
{
	int					id;
	pthread_t			thread;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*rigth_fork;
	long long			last_meal_time;
	int					meals_eaten;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					must_eat_count;
}	t_philosopher;

typedef struct s_data
{
	int					num_philo;
	pthread_mutex_t		*forks;
	t_philosopher		*philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					must_eat_count;
	long long			start_time;
	pthread_mutex_t		print_mutex;					
}	t_data;

long long	get_time_in_ms(void);
void		philo_routine(void *arg);
void		init_philo(t_data *data);
void		init_mutexes(t_data *data);
void		destroy_mutexes(t_data *data);

#endif