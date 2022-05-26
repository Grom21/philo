/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etisha <etisha@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 13:24:01 by etisha            #+#    #+#             */
/*   Updated: 2022/05/14 13:24:04 by etisha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_print(t_philo *philo, char *str)
{
	long long	time;

	sem_wait(philo->print);
	time = ft_get_time() - philo->time_start;
	printf("%lld %d %s\n", time, philo->number, str);
	sem_post(philo->print);
}

void	ft_kill_all(t_input *input, t_philo *philo, int count_proc)
{
	int	i;

	i = 0;
	while (i < count_proc)
	{
		kill(input->pid[i], 1);
		i++;
	}
	i = 0;
	while (i < input->count)
	{
		sem_close(philo[i].philo);
		i++;
	}
	sem_close(input->print);
	sem_close(input->forks);
	sem_close(input->deth);
}

int	main(int argc, char **argv)
{
	t_input	input;
	t_philo	philo[PHILO_MAX];
	pid_t	pid_kids[PHILO_MAX];

	input.pid = pid_kids;
	if (argc != 5 && argc != 6)
		return (1);
	if (ft_exam (argc, argv, &input))
		return (1);
	ft_init_sem (&input);
	ft_philo_init(&input, philo);
	ft_philo_start(&input, philo);
	sem_wait(input.deth);
	ft_kill_all(&input, philo, input.count);
	return (0);
}
