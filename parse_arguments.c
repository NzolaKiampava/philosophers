/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 12:00:59 by nkiampav          #+#    #+#             */
/*   Updated: 2024/11/09 12:04:21 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_valid_number(char *str)
{
	long long	num;
	int			i;

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

static int	validate_input(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf(STR_USAGE);
		return (1);
	}
	if (!is_valid_number(argv[1]) || !is_valid_number(argv[2])
		|| !is_valid_number(argv[3]) || !is_valid_number(argv[4])
		|| (argc == 6 && !is_valid_number(argv[5])))
	{
		printf("Error: Invalid arguments\n");
		return (1);
	}
	return (0);
}

int	parse_args(int argc, char **argv, t_data *data)
{
	if (validate_input(argc, argv))
		return (1);
	data->num_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->must_eat_count = ft_atoi(argv[5]);
	else
		data->must_eat_count = -1;
	data->someone_died = 0;
	if (data->num_philosophers <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0
		|| (data->must_eat_count <= 0 && argc == 6))
	{
		printf("Error: Invalid arguments\n");
		return (1);
	}
	return (0);
}
