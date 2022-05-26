/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etisha <etisha@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 13:24:36 by etisha            #+#    #+#             */
/*   Updated: 2022/05/14 13:24:38 by etisha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <semaphore.h>
# include <stdlib.h>
# include <pthread.h>
# include <signal.h>
# include <string.h>

# define PHILO_MAX 250

typedef struct s_input
{
	int				count;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				must_eat;
	long long		time_start;
	sem_t			*print;
	sem_t			*forks;
	sem_t			*deth;
	pid_t			*pid;
}	t_input;

typedef struct s_philo
{
	pthread_t		overseer;
	int				count;
	int				number;
	int				numberr;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				must_eat;
	int				count_eat;
	long long		time_start;
	long long		t_eat;
	sem_t			*print;
	sem_t			*forks;
	sem_t			*philo;
	sem_t			*deth;
}	t_philo;

int			ft_exam(int argc, char **argv, t_input *input);
long long	ft_get_time(void);
void		ft_init_sem(t_input *input);
void		ft_philo_init(t_input *input, t_philo *philo);
void		ft_philo_start(t_input *input, t_philo *philo);
void		ft_simulate(t_philo *philo);
void		ft_print(t_philo *philo, char *str);
void		*ft_overseer(void *p);
void		ft_kill_all(t_input *input, t_philo *philo, int count_proc);

#endif
