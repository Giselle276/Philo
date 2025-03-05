/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 12:04:26 by gmaccha-          #+#    #+#             */
/*   Updated: 2025/02/22 02:35:06 by gmaccha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_print(const char *error)
{
	printf(RED "🚨%s🚨\n"RST, error);
	return (-1);
}

long	gettime(t_time_code time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
	{
		error_print("Gettimeofday failed");
		return (-1);
	}
	if (SECOND == time_code)
		return (tv.tv_sec + (tv.tv_usec / 1000000));
	else if (MILISECOND == time_code)
		return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	else if (MICROSECOND == time_code)
		return ((tv.tv_sec * 1000000) + tv.tv_usec);
	error_print("Error input to gettime!");
	return (-1);
}

void	precise_usleep(long usec, t_table *table)
{
	long	start;
	long	elapsed;
	long	rem;

	start = gettime(MICROSECOND);
	while (gettime(MICROSECOND) - start < usec)
	{
		if (routine_finished(table))
			break ;
		elapsed = gettime(MICROSECOND) - start;
		rem = usec - elapsed;
		if (rem > 1000)
			usleep(rem / 2);
		else
		{
			while (gettime(MICROSECOND) - start < usec)
				;
		}
	}
}

void	clean(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < table->num_philo)
	{
		philo = table->philos + i;
		safe_mutex_handle(&philo->philo_mutex, DESTROY);
	}
	safe_mutex_handle(&table->print_mutex, DESTROY);
	safe_mutex_handle(&table->table_mutex, DESTROY);
	free(table->forks);
	free(table->philos);
}

int	safe_mutex_handle(t_mtx *mutex, t_opcode opcode)
{
	int	status;

	if (opcode == LOCK)
		status = pthread_mutex_lock(mutex);
	else if (opcode == UNLOCK)
		status = pthread_mutex_unlock(mutex);
	else if (opcode == INIT)
		status = pthread_mutex_init(mutex, NULL);
	else if (opcode == DESTROY)
		status = pthread_mutex_destroy(mutex);
	else
	{
		error_print("Error opcode for mutex handle");
		return (-1);
	}
	return (0);
}
