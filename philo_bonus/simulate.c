/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etisha <etisha@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 13:24:48 by etisha            #+#    #+#             */
/*   Updated: 2022/05/14 13:24:50 by etisha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	sem_wait(philo->forks);
	ft_print(philo, "has taken a fork");
	sem_wait(philo->forks);
	ft_print(philo, "has taken a fork");
	ft_print(philo, "is eating");
	sem_wait(philo->philo);
	philo->t_eat = ft_get_time();
	philo->count_eat++;
	sem_post(philo->philo);
	ft_usleep(philo->time_eat);
	sem_post(philo->forks);
	sem_post(philo->forks);
}

void	ft_simulate(t_philo *philo)
{
	pthread_create(&philo->overseer, NULL, ft_overseer, philo);
	pthread_detach(philo->overseer);
	while (1)
	{
		ft_philo_eat(philo);
		ft_philo_sleep(philo);
		ft_philo_thinking(philo);
	}
}
