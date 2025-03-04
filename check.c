/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-28 10:57:31 by gmaccha-          #+#    #+#             */
/*   Updated: 2025-02-28 10:57:31 by gmaccha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline bool	ft_is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static inline bool	ft_is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

const char	*valid_str_num(const char *str)
{
	int			len;
	const char	*number;

	len = 0;
	while (ft_is_space(*str))
		str++;
	if (*str == '-')
		return (error_print("Input must be a positive number"), NULL);
	if (*str == '+')
		str++;
	if (!ft_is_digit(*str))
		return (error_print("The input is not a number"), NULL);
	number = str;
	while (ft_is_digit(*str++))
		len++;
	if (len > 10)
		return (error_print("The value is too big, INT_MAX is the limit"),
			NULL);
	return (number);
}

long	ft_atol(const char *str)
{
	long	num;

	str = valid_str_num(str);
	if (!str)
		return (-1);
	num = 0;
	while (*str)
	{
		if (!ft_is_digit(*str))
		{
			return (error_print("The input contains characters"), -1);
		}
		num = (num * 10) + (*str++ - 48);
	}
	if (num > INT_MAX)
	{
		return (error_print("The value is too big, INT_MAX is the limit"), -1);
	}
	return (num);
}

int	check_input(t_table *table, char **argv)
{
	table->num_philo = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	if (table->num_philo == -1 || table->time_to_die == -1
		|| table->time_to_eat == -1 || table->time_to_sleep == -1)
		return (-1);
	table->time_to_die = ft_atol(argv[2]) * 1000;
	table->time_to_eat = ft_atol(argv[3]) * 1000;
	table->time_to_sleep = ft_atol(argv[4]) * 1000;
	if (table->time_to_die < 60000 || table->time_to_eat < 60000
		|| table->time_to_sleep < 60000)
	{
		error_print("Given time must be more than 60ms");
		return (-1);
	}
	if (argv[5])
		table->num_limit_meals = ft_atol(argv[5]);
	else
		table->num_limit_meals = -1;
	return (0);
}
