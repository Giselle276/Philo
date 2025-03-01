/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 11:59:01 by gmaccha-          #+#    #+#             */
/*   Updated: 2025/02/22 02:35:41 by gmaccha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_table	table;

	if (argc != 5 && argc != 6)
	{
		error_print("Error input:\n"
			G"Correct Input: ./philo num_philo time_dead time_sleep time_think"
			" [limit_eat_philo]\n"
			G"Run as:./philo 2 800 200 200 [5]" RST);
		return (1);
	}
	if (check_input(&table, argv) == -1)
		return (1);
	if (data_init(&table) == -1)
		return (1);
	if (dinner_start(&table) == -1)
		return (1);
	clean(&table);
	return (0);
}
