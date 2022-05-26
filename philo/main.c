/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etisha <etisha@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 17:37:34 by etisha            #+#    #+#             */
/*   Updated: 2022/05/01 17:37:48 by etisha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print(t_philo *philo, char *str)
{
	long long	time;

	pthread_mutex_lock(philo->mutex_print);
	time = ft_get_time() - philo->t_start;
	printf("%lld %d %s\n", time, philo->number, str);
	pthread_mutex_unlock(philo->mutex_print);
}

int	main(int argc, char **argv)
{
	t_philo			philo[PHILO_MAX];
	pthread_mutex_t	forks[PHILO_MAX];
	t_input			input;

	if (argc != 5 && argc != 6)
		return (1);
	if (ft_exam (argc, argv, &input))
		return (1);
	if (ft_fork_init(forks, &input.count))
		return (1);
	if (ft_philo_init(philo, &input, forks))
		return (1);
	if (ft_start(philo))
		return (1);
	if (ft_inspektor(philo, &input, forks))
		return (1);
	return (0);
}
