/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inspector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etisha <etisha@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 17:38:35 by etisha            #+#    #+#             */
/*   Updated: 2022/05/01 17:38:37 by etisha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_destoy_mutex(t_philo *philo, pthread_mutex_t *forks, \
t_input *input)
{
	int	i;

	i = 0;
	while (i < input->count)
	{
		pthread_mutex_destroy(&philo[i].mutex_philo);
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	pthread_mutex_destroy(&input->mutex_print);
}

static int	ft_get_time_monitor(long long *time)
{
	struct timeval	t;

	if (gettimeofday(&t, NULL))
		return (1);
	*time = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	return (0);
}

static int	ft_check_overeat(t_philo *philo, t_input *input, int *all_eat, \
pthread_mutex_t *forks)
{	
	if (input->must_eat != -1 && philo->overeat != 1 \
	&& philo->count_eat >= input->must_eat)
	{
		philo->overeat = 1;
		(*all_eat)--;
		if (*all_eat == 0)
		{
			pthread_mutex_lock(philo[0].mutex_print);
			ft_destoy_mutex(philo, forks, input);
			return (1);
		}
	}
	return (0);
}

int	ft_inspektor(t_philo *philo, t_input *input, pthread_mutex_t *forks)
{
	int			i;
	long long	time;
	int			all_eat;

	all_eat = input->count;
	while (1)
	{
		i = -1;
		while (++i < input->count)
		{
			ft_get_time_monitor(&time);
			pthread_mutex_lock(&philo[i].mutex_philo);
			if (ft_check_overeat(&philo[i], input, &all_eat, forks))
				return (0);
			if ((time - philo[i].t_eat) > input->time_die)
			{
				ft_print(&philo[i], "died");
				pthread_mutex_lock(philo[0].mutex_print);
				ft_destoy_mutex(philo, forks, input);
				return (0);
			}
			pthread_mutex_unlock(&philo[i].mutex_philo);
		}
	}
	return (1);
}
