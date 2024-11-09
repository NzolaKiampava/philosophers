/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 10:35:17 by nkiampav          #+#    #+#             */
/*   Updated: 2024/11/06 09:59:44 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

# define STR_USAGE "\033[36mUsage: ./philo [num_philosophers] [time_to_die] \
[time_to_eat] [time_to_sleep] [num_meals]\n\033[0m"

# define STR_FORK "\033[32m has taken a fork\033[0m"
# define STR_SLEEP "\033[36m is sleeping\033[0m"
# define STR_EAT "\033[35m is eating\033[0m"
# define STR_THINK "\033[1;37m is thinking\033[0m"

/* Structures */
typedef struct s_philosopher
{
	int					id;
	int					left_fork;
	int					right_fork;
	int					meals_eaten;
	long long			last_meal_time;
	struct s_data		*data;
	pthread_t			thread;
}		t_philosopher;

typedef struct s_data
{
	int					num_philosophers;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					must_eat_count;
	int					someone_died;
	long long			start_time;
	pthread_mutex_t		*forks;
	pthread_mutex_t		write_lock;
	t_philosopher		*philosophers;
}		t_data;

/* Time functions */
long long	get_time(void);
void		smart_sleep(long long time);

/* Initialization functions */
int			init_data(t_data *data);
int			init_philosophers(t_data *data);
int			init_mutexes(t_data *data);
int			init_simulation(t_data *data);

/* Philosopher actions */
void		*philosopher_routine(void *arg);
void		philo_eat(t_philosopher *philo);
void		philo_sleep(t_philosopher *philo);
void		philo_think(t_philosopher *philo);

/* Monitor functions */
void		*death_monitor(void *arg);
int			check_if_all_ate(t_data *data);

/* Utility functions */
void		print_status(t_data *data, int id, char *status);
int			ft_atoi(const char *str);
void		cleanup_simulation(t_data *data);

/* Parse Arguments functions*/
int			is_valid_number(char *str);
int			parse_args(int argc, char **argv, t_data *data);

#endif
