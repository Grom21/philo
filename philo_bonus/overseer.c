/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overseer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etisha <etisha@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 13:24:24 by etisha            #+#    #+#             */
/*   Updated: 2022/05/14 13:24:25 by etisha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_print_deth(t_philo *philo, char *str)
{
	long long	time;

	sem_wait(philo->print);
	time = ft_get_time() - philo->time_start;
	printf("%lld %d %s\n", time, philo->number, str);
}

static int	ft_get_time_overseer(long long *time)
{
	struct timeval	t;

	if (gettimeofday(&t, NULL))
		return (1);
	*time = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	return (0);
}

void	*ft_overseer(void *p)
{
	t_philo		*philo;
	long long	time;

	philo = p;
	while (1)
	{
		ft_get_time_overseer(&time);
		sem_wait(philo->philo);
		if (philo->numberr == philo->count && \
		philo->must_eat > 0 && philo->count_eat >= philo->must_eat)
		{
			sem_wait(philo->print);
			sem_post(philo->deth);
			return (NULL);
		}
		if ((time - philo->t_eat) > philo->time_die)
		{
			ft_print_deth(philo, "died");
			sem_post(philo->deth);
			return (NULL);
		}
		sem_post(philo->philo);
	}
	return (NULL);
}
