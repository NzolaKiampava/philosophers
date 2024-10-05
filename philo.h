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
# include <string.h>

# define BOLD_WHITE "\033[1;37m"
# define PURPLE "\033[35m"
# define CYAN   "\033[36m"
# define GREEN  "\033[32m"
# define RESET  "\033[0m"

# define STR_USAGE CYAN "%s Usage: ./philo <number_of_philosophers> \
<time_to_die> <time_to_eat> <time_to_sleep> \
[must_eat_count]\n" RESET

# define STR_FORK GREEN "has taken a fork" RESET
# define STR_SLEEP CYAN "is sleeping" RESET
# define STR_EAT PURPLE "is eating" RESET
# define STR_THINK BOLD_WHITE "is thinking" RESET

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
int		init_philo(t_data *data);
int		init_mutexes(t_data *data);
void		destroy_mutexes(t_data *data);

// Core simulation functions
void		start_simulation(t_data *data);

// Action and state management
void		eat(t_philosopher *philo, t_data *data);
void		sleep_and_think(t_philosopher *philo, t_data *data);

#endif
