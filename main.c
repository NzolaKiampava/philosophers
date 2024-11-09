/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:54:38 by nkiampav          #+#    #+#             */
/*   Updated: 2024/11/06 09:53:07 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data		data;
	int			i;

	i = -1;
	if (parse_args(argc, argv, &data))
		return (1);
	if (init_simulation(&data))
	{
		printf("Error: Failed to initialize simulation\n");
		return (1);
	}
	while (++i < data.num_philosophers)
		pthread_join(data.philosophers[i].thread, NULL);
	cleanup_simulation(&data);
	return (0);
}
