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

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (c);
	return (0);
}

int	ft_atoi(const char *str)
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

void	print_status(t_data *data, int id, char *status)
{
	pthread_mutex_lock(&data->write_lock);
	if (!data->someone_died)
		printf("%lld %d %s\n", get_time() - data->start_time, id + 1, status);
	pthread_mutex_unlock(&data->write_lock);
}

void	cleanup_simulation(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_philosophers)
		pthread_mutex_destroy(&data->forks[i]);
	pthread_mutex_destroy(&data->write_lock);
	free(data->forks);
	free(data->philosophers);
}
