/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-28 10:08:33 by gmaccha-          #+#    #+#             */
/*   Updated: 2025-02-28 10:08:33 by gmaccha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo_status status, t_philo *philo)
{
	long	elapsed;

	elapsed = gettime(MILISECOND) - philo->table->start_simulation;
	safe_mutex_handle(&philo->table->print_mutex, LOCK);
	if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
		&& !simulation_finished(philo->table))
		printf(W"%-6ld"RST" %d has taken a fork\n", elapsed, philo->id);
	else if (status == EATING && !simulation_finished(philo->table))
		printf(W"%-6ld"M" %d is eating\n"RST, elapsed, philo->id);
	else if (status == SLEEPING && !simulation_finished(philo->table))
		printf(W"%-6ld"C" %d is sleeping\n"RST, elapsed, philo->id);
	else if (status == THINKING && !simulation_finished(philo->table))
		printf(W"%-6ld"Y" %d is thinking\n"RST, elapsed, philo->id);
	else if (status == DIED)
		printf(RED"%-6ld %d died\n"RST, elapsed, philo->id);
	safe_mutex_handle(&philo->table->print_mutex, UNLOCK);
}
