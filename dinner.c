/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-25 09:02:19 by gmaccha-          #+#    #+#             */
/*   Updated: 2025-02-25 09:02:19 by gmaccha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philos_threads(t_table *table)
{
	int	i;

	i = -1;
	if (table->num_philo == 1)
	{
		if (safe_thread_handle(&table->philos[0].thread_id, one_philo,
				&table->philos[0], CREATE) == -1)
			return (-1);
	}
	else
	{
		while (++i < table->num_philo)
		{
			if (safe_thread_handle(&table->philos[i].thread_id,
					philo_routine, &table->philos[i], CREATE) == -1)
				return (-1);
		}
	}
	return (0);
}

int	dinner_start(t_table *table)
{
	int	i;

	if (table->num_limit_meals == 0)
		return (0);
	if (init_philos_threads(table) == -1)
		return (-1);
	if (safe_thread_handle(&table->controller, controller, table,
			CREATE) == -1)
		return (-1);
	table->start_routine = gettime(MILISECOND);
	set_bool(&table->table_mutex, &table->all_threads_ready, true);
	i = -1;
	while (++i < table->num_philo)
	{
		if (safe_thread_handle(&table->philos[i].thread_id, NULL, NULL,
				JOIN) == -1)
			return (-1);
	}
	set_bool(&table->table_mutex, &table->stop_routine, true);
	if (safe_thread_handle(&table->controller, NULL, NULL, JOIN) == -1)
		return (-1);
	return (0);
}
