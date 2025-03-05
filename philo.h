/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 02:40:54 by gmaccha-          #+#    #+#             */
/*   Updated: 2025/02/22 02:45:50 by gmaccha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <errno.h>

# define RST	"\033[0m"
# define RED	"\033[1;31m"
# define G		"\033[1;32m"
# define Y		"\033[1;33m"
# define B		"\033[1;34m"
# define M		"\033[1;35m"
# define C		"\033[1;36m"
# define W		"\033[1;37m"

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}	t_philo_status;

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}	t_opcode;

typedef enum e_time
{
	SECOND,
	MILISECOND,
	MICROSECOND,
}	t_time_code;

typedef pthread_mutex_t	t_mtx;
typedef struct s_table	t_table;

typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;
}			t_fork;

typedef struct s_philo
{
	int			id;
	long		meals_count;
	bool		full_meal;
	long		last_meal_time;
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id;
	t_mtx		philo_mutex;
	t_table		*table;
}				t_philo;

typedef struct s_table
{
	long		num_philo;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		num_limit_meals;
	long		start_routine;
	bool		stop_routine;
	bool		all_threads_ready;
	long		num_threads_running;
	pthread_t	controller;
	t_mtx		table_mutex;
	t_mtx		print_mutex;
	t_fork		*forks;
	t_philo		*philos;
}				t_table;

int			error_print(const char *error);
int			check_input(t_table *table, char **argv);
int			data_init(t_table *table);
int			safe_thread_handle(pthread_t *thread, void *(*foo)(void *),
				void *data, t_opcode opcode);
int			safe_mutex_handle(t_mtx *mutex, t_opcode opcode);
void		set_bool(t_mtx *mutex, bool *dest, bool value);
bool		get_bool(t_mtx *mutex, bool *value);
long		get_long(t_mtx *mutex, long *value);
void		set_long(t_mtx *mutex, long *dest, long value);
bool		routine_finished(t_table *table);
void		wait_all_threads(t_table *table);
long		gettime(t_time_code time_code);
void		precise_usleep(long usec, t_table *table);
void		print_status(t_philo_status status, t_philo *philo);
int			dinner_start(t_table *table);
void		*controller(void *data);
void		*one_philo(void *arg);
void		increase_long(t_mtx *mutex, long *value);
bool		all_threads_running(t_mtx *mutex, long *threads,
				long num_philo);
void		wait_all_threads(t_table *table);
void		clean(t_table *table);
void		thinking(t_philo *philo);
int			init_philos_threads(t_table *table);
void		*philo_routine(void *data);
int			safe_thread_handle(pthread_t *thread, void *(*foo)(void *),
				void *data, t_opcode opcode);
long		ft_atol(const char *str);
const char	*valid_str_num(const char *str);
void		philo_init(t_table *table);

#endif
