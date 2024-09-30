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
	int			i;
	long long 	cur_time;

	i = 0;
	while (1)
	{
		while (i < data->num_philo)
		{
			cur_time = get_time_in_ms();
			pthread_mutex_lock(&data->print_mutex);
			if (cur_time - data->philo[i].last_meal_time > data->time_to_die)
			{
				cur_time = cur_time - data->start_time;
				printf("%lld %d died\n", cur_time, data->philo[i].id);
				return (1);
			}
			pthread_mutex_unlock(&data->print_mutex);
		}
		usleep(1000);
	}
}
