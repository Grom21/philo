/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etisha <etisha@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 17:39:40 by etisha            #+#    #+#             */
/*   Updated: 2022/05/01 17:39:42 by etisha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_usleep(int time_sleep)
{
	long long	time_start_sleep;
	long long	time_now;

	time_start_sleep = ft_get_time();
	time_now = ft_get_time();
	while (time_now - time_start_sleep < time_sleep)
	{
		usleep(100);
		time_now = ft_get_time();
	}
}

static void	ft_philo_sleep(t_philo *philo)
{
	ft_print(philo, "is sleeping");
	ft_usleep(philo->time_sleep);
}

static void	ft_philo_thinking(t_philo *philo)
{
	ft_print(philo, "is thinking");
}

static void	ft_philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->min_fork);
	ft_print(philo, "has taken a fork");
	pthread_mutex_lock(philo->max_fork);
	ft_print(philo, "has taken a fork");
	ft_print(philo, "is eating");
	pthread_mutex_lock(&philo->mutex_philo);
	philo->t_eat = ft_get_time();
	philo->count_eat++;
	pthread_mutex_unlock(&philo->mutex_philo);
	ft_usleep(philo->time_eat);
	pthread_mutex_unlock(philo->max_fork);
	pthread_mutex_unlock(philo->min_fork);
}

void	*ft_simulation(void *philo)
{
	if (((t_philo *)philo)->number % 2 == 0)
		usleep(2500);
	while (1)
	{
		ft_philo_eat((t_philo *) philo);
		ft_philo_sleep((t_philo *) philo);
		ft_philo_thinking((t_philo *) philo);
	}
	return (NULL);
}
