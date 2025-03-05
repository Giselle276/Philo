/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:15:04 by gmaccha-          #+#    #+#             */
/*   Updated: 2025/02/22 02:48:52 by gmaccha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks(t_philo *philo, t_fork *forks, int philo_position)
{
	int	num_philo;

	num_philo = philo->table->num_philo;
	philo->first_fork = &forks[(philo_position + 1) % num_philo];
	philo->second_fork = &forks[philo_position];
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[philo_position];
		philo->second_fork = &forks[(philo_position + 1) % num_philo];
	}
}

void	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->num_philo)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full_meal = false;
		philo->meals_count = 0;
		philo->table = table;
		safe_mutex_handle(&philo->philo_mutex, INIT);
		assign_forks(philo, table->forks, i);
	}
}

int	data_init(t_table *table)
{
	int	i;

	i = -1;
	table->stop_routine = false;
	table->all_threads_ready = false;
	table->num_threads_running = 0;
	table->philos = malloc(sizeof(t_philo) * table->num_philo);
	if (!table->philos)
		return (-1);
	if (safe_mutex_handle(&table->table_mutex, INIT) == -1)
		return (-1);
	if (safe_mutex_handle(&table->print_mutex, INIT) == -1)
		return (-1);
	table->forks = malloc(sizeof(t_fork) * table->num_philo);
	if (!table ->forks)
		return (-1);
	while (++i < table->num_philo)
	{
		if (safe_mutex_handle(&table->forks[i].fork, INIT) == -1)
			return (-1);
		table->forks[i].fork_id = i;
	}
	philo_init(table);
	return (0);
}
