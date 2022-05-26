/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etisha <etisha@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 13:23:50 by etisha            #+#    #+#             */
/*   Updated: 2022/05/14 13:23:53 by etisha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_init_sem(t_input *input)
{
	sem_unlink("print");
	sem_unlink("forks");
	sem_unlink("deth");
	input->print = sem_open("print", O_CREAT, 0600, 1);
	input->forks = sem_open("forks", O_CREAT, 0600, input->count);
	input->deth = sem_open("deth", O_CREAT, 0600, 1);
	sem_wait(input->deth);
}

static void	ft_sem_philo(t_philo *philo, int i)
{
	char	str[PHILO_MAX];

	memset(&str, 'p', i + 21);
	str[i + 21] = '\0';
	sem_unlink(str);
	philo->philo = sem_open(str, O_CREAT, 0600, 1);
}

void	ft_philo_init(t_input *input, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < input->count)
	{
		philo[i].count = input->count;
		philo[i].number = i + 1;
		philo[i].numberr = i + 1;
		philo[i].time_die = input->time_die;
		philo[i].time_eat = input->time_eat;
		philo[i].time_sleep = input->time_sleep;
		philo[i].must_eat = input->must_eat;
		philo[i].count_eat = 0;
		philo[i].time_start = input->time_start;
		philo[i].t_eat = input->time_start;
		philo[i].print = input->print;
		philo[i].forks = input->forks;
		philo[i].deth = input->deth;
		ft_sem_philo(&philo[i], i);
		i++;
	}
}

void	ft_philo_start(t_input *input, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < input->count)
	{
		input->pid[i] = fork();
		if (input->pid[i] == 0)
			ft_simulate(&philo[i]);
		else if (input->pid[i] == -1)
		{
			ft_kill_all(input, philo, i);
			exit(1);
		}
		i++;
		usleep(2500);
	}
}
