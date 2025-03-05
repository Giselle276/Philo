/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-28 10:55:54 by gmaccha-          #+#    #+#             */
/*   Updated: 2025-02-28 10:55:54 by gmaccha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_all_threads(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->all_threads_ready))
		;
}

bool	all_threads_running(t_mtx *mutex, long *threads,
		long num_philo)
{
	bool	ret;

	ret = false;
	safe_mutex_handle(mutex, LOCK);
	if (*threads == num_philo)
		ret = true;
	safe_mutex_handle(mutex, UNLOCK);
	return (ret);
}

void	increase_long(t_mtx *mutex, long *value)
{
	safe_mutex_handle(mutex, LOCK);
	(*value)++;
	safe_mutex_handle(mutex, UNLOCK);
}

int	safe_thread_handle(pthread_t *thread, void *(*foo)(void *),
		void *data, t_opcode opcode)
{
	int	status;

	if (opcode == CREATE)
		status = pthread_create(thread, NULL, foo, data);
	else if (opcode == JOIN)
		status = pthread_join(*thread, NULL);
	else if (opcode == DETACH)
		status = pthread_detach(*thread);
	else
	{
		error_print("Error opcode for thread_handle:"
			" use >CREATE> >JOIN> >DETACH>");
		return (-1);
	}
	return (0);
}
