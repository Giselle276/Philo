/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-28 10:26:43 by gmaccha-          #+#    #+#             */
/*   Updated: 2025-02-28 10:26:43 by gmaccha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	t_to_die;

	if (get_bool(&philo->philo_mutex, &philo->full_meal))
		return (false);
	elapsed = gettime(MILISECOND) - get_long(&philo->philo_mutex,
			&philo->last_meal_time);
	t_to_die = philo->table->time_to_die / 1000;
	if (elapsed > t_to_die)
		return (true);
	return (false);
}

void	*controller(void *data)
{
	int		i;
	t_table	*table;

	table = (t_table *)data;
	while (!all_threads_running(&table->table_mutex,
			&table->num_threads_running, table->num_philo))
		;
	while (!routine_finished(table))
	{
		i = -1;
		while (++i < table->num_philo && !routine_finished(table))
		{
			if (philo_died(table->philos + i))
			{
				set_bool(&table->table_mutex, &table->stop_routine, true);
				print_status(DIED, table->philos + i);
			}
		}
	}
	return (NULL);
}
