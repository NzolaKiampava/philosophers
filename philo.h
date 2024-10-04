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

# define CYAN "\e[36m"
# define GREEN "\e[32m"

typedef struct s_philosopher
{
	int					id;
	pthread_t			thread;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	long long			last_meal_time;
	int					meals_eaten;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					must_eat_count;
	struct s_data		*data; // Pointer to shared data structure
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
	pthread_mutex_t		print_mutex; // Mutex for printing syncronized messages					
}	t_data;

// Utility functions
long long	get_time_in_ms(void);
int			check_death(t_data *data);

// Philosophers functions
void		*philo_routine(void *arg);
void		init_philo(t_data *data);
void		init_mutexes(t_data *data);
void		destroy_mutexes(t_data *data);

// Core simulation functions
void		start_simulation(t_data *data);

// Action and state management
void		eat(t_philosopher *philo, t_data *data);
void		sleep_and_think(t_philosopher *philo, t_data *data);

#endif
