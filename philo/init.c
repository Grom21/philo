/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etisha <etisha@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 17:38:16 by etisha            #+#    #+#             */
/*   Updated: 2022/05/01 17:38:19 by etisha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_fork_init(pthread_mutex_t *forks, int *count)
{
	int	i;

	i = 0;
	while (i < *count)
	{
		if (pthread_mutex_init(&forks[i], NULL))
			return (1);
		i++;
	}
	return (0);
}

static void	ft_give_forks(t_philo *philo, pthread_mutex_t *forks, int i)
{
	if (i == 0)
	{
		philo->min_fork = &forks[i];
		philo->max_fork = &forks[philo[i].count - 1];
	}
	else
	{
		philo->min_fork = &forks[i - 1];
		philo->max_fork = &forks[i];
	}
}

int	ft_philo_init(t_philo *philo, t_input *input, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&input->mutex_print, NULL))
		return (1);
	while (i < input->count)
	{
		philo[i].count = input->count;
		philo[i].time_die = input->time_die;
		philo[i].time_eat = input->time_eat;
		philo[i].time_sleep = input->time_sleep;
		philo[i].count_eat = 0;
		philo[i].must_eat = input->must_eat;
		philo[i].t_start = input->time_start;
		philo[i].number = i + 1;
		ft_give_forks(&philo[i], forks, i);
		philo[i].mutex_print = &input->mutex_print;
		if (pthread_mutex_init(&philo[i].mutex_philo, NULL))
			return (1);
		i++;
	}
	return (0);
}

int	ft_start(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo[0].count)
	{
		philo[i].t_eat = ft_get_time();
		if (pthread_create(&philo[i].philo, NULL, ft_simulation, &philo[i]))
			return (1);
		pthread_detach(philo[i].philo);
		i++;
	}
	return (0);
}
