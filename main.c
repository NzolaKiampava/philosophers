/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:54:38 by nkiampav          #+#    #+#             */
/*   Updated: 2024/09/30 14:11:04 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_arguments(int argc, char **argv, t_data *data)
{
	if (argc != 5 && argc != 6)
	{
		printf(STR_USAGE, argv[0]);
		return (1);
	}
	data->num_philo = atoi(argv[1]);
	data->time_to_die = atoi(argv[2]);
	data->time_to_eat = atoi(argv[3]);
	data->time_to_sleep = atoi(argv[4]);
	if (argc == 6)
		data->must_eat_count = atoi(argv[5]);
	else
		data->must_eat_count = -1;
	return (0);
}

int	main(int argc, char **argv)
{
    t_data data;

    // Parse command-line arguments
    if (parse_arguments(argc, argv, &data)) {
        return (1); // Error in parsing
    }

    // Initialize mutexes
    if (init_mutexes(&data) != 0) {
        return (1); // Error in mutex initialization
    }

    // Initialize philosophers
    if (init_philo(&data) != 0) {
        destroy_mutexes(&data); // Clean up mutexes if initialization fails
        return (1); // Error in philosopher initialization
    }

    // Start the simulation
    start_simulation(&data);

    // Clean up resources after the simulation completes
    destroy_mutexes(&data); // Ensure all mutexes are destroyed
    free(data.philo); // Free the philosophers array
    free(data.forks); // Free the forks array

    return (0); // Successful termination
}
