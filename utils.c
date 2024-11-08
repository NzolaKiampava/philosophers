/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 10:36:12 by nkiampav          #+#    #+#             */
/*   Updated: 2024/11/08 10:38:30 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int ft_isdigit(int c)
{
    if (c >= '0' && c <= '9')
        return (c);
    return (0);
}

static int	ft_atoi(const char *str)
{
	int	num;
	int	isneg;
	int	i;

	num = 0;
	isneg = 1;
	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'
			|| str[i] == '\n' || str[i] == '\r'
			|| str[i] == '\v' || str[i] == '\f'))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		isneg *= -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		num = (num * 10) + (str[i] - '0');
		i++;
	}
	return (num * isneg);
}

void print_status(t_data *data, int id, char *status)
{
    pthread_mutex_lock(&data->write_lock);
    if (!data->someone_died)
        printf("%lld %d %s\n", get_time() - data->start_time, id + 1, status);
    pthread_mutex_unlock(&data->write_lock);
}

int is_valid_number(char *str)
{
    long long num;
    int i;

    num = 0;
    i = 0;
    if (str[0] == '-')
        return (0);
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return (0);
        num = (num * 10) + (str[i] - '0');
        if (num > INT_MAX)
            return (0);
        i++;
    }
    return (1);
}

int parse_args(int argc, char **argv, t_data *data)
{
    if (argc != 5 && argc != 6)
    {
        printf(STR_USAGE);
        return (1);
    }
    if (!is_valid_number(argv[1]) || !is_valid_number(argv[2]) || 
        !is_valid_number(argv[3]) || !is_valid_number(argv[4]) || 
        (argc == 6 && !is_valid_number(argv[5])))
    {
        printf("Error: Invalid arguments\n");
        return (1);
    }
    data->num_philosophers = ft_atoi(argv[1]);
    data->time_to_die = ft_atoi(argv[2]);
    data->time_to_eat = ft_atoi(argv[3]);
    data->time_to_sleep = ft_atoi(argv[4]);
    data->must_eat_count = (argc == 6) ? ft_atoi(argv[5]) : -1;
    data->someone_died = 0;
    if (data->num_philosophers <= 0 || data->time_to_die <= 0 || 
        data->time_to_eat <= 0 || data->time_to_sleep <= 0 || 
        (data->must_eat_count <= 0 && argc == 6))
    {
        printf("Error: Invalid arguments\n");
        return (1);
    }
    return (0);
}

void	cleanup_simulation(t_data *data)
{
    int	i;

    for (i = 0; i < data->num_philosophers; i++)
        pthread_mutex_destroy(&data->forks[i]);
    pthread_mutex_destroy(&data->write_lock);
    free(data->forks);
    free(data->philosophers);
}
