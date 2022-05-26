/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exam.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etisha <etisha@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 17:38:01 by etisha            #+#    #+#             */
/*   Updated: 2022/05/01 17:38:04 by etisha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_get_time(void)
{
	struct timeval	t;

	if (gettimeofday(&t, NULL))
		return (1);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

static int	ft_isdigit(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{	
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (-1);
	}
	return (0);
}

static int	ft_atoi(const char *str, int *count)
{
	int				i;
	long long int	result;

	if (ft_isdigit(str))
	{
		write (2, "Error\nWrong arguments!\n", 23);
		return (-1);
	}
	i = 0;
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		if (result > 2147483647 || result == 0)
			return (-1);
		i++;
	}
	*count = result;
	return (0);
}

int	ft_exam(int argc, char **argv, t_input *input)
{
	if (argc >= 5)
	{
		if (ft_atoi(argv[1], &input->count))
			return (1);
		if (ft_atoi(argv[2], &input->time_die))
			return (1);
		if (ft_atoi(argv[3], &input->time_eat))
			return (1);
		if (ft_atoi(argv[4], &input->time_sleep))
			return (1);
		input->must_eat = -1;
	}
	if (argc == 6)
	{
		if (ft_atoi(argv[5], &input->must_eat))
			return (1);
	}
	input->time_start = ft_get_time();
	return (0);
}
