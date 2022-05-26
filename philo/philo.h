/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etisha <etisha@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 17:39:28 by etisha            #+#    #+#             */
/*   Updated: 2022/05/01 17:39:31 by etisha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>

# define PHILO_MAX 250

typedef struct s_input
{
	int				count;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				must_eat;
	long long		time_start;
	pthread_mutex_t	mutex_print;
}	t_input;

typedef struct s_philo
{
	pthread_t				philo;
	int						count;
	int						time_die;
	int						time_eat;
	int						time_sleep;
	int						count_eat;
	int						must_eat;
	int						number;
	long long				t_start;
	long long				t_eat;
	pthread_mutex_t			*min_fork;
	pthread_mutex_t			*max_fork;
	pthread_mutex_t			*mutex_print;
	pthread_mutex_t			mutex_philo;
	volatile sig_atomic_t	overeat;
}	t_philo;

int			ft_exam(int argc, char **argv, t_input *input);
long long	ft_get_time(void);
int			ft_fork_init(pthread_mutex_t *forks, int *count);
int			ft_philo_init(t_philo *philo, t_input *input, \
pthread_mutex_t *forks);
int			ft_start(t_philo *philo);
void		*ft_simulation(void *philo);
int			ft_inspektor(t_philo *philo, t_input *input, \
pthread_mutex_t *forks);
void		ft_print(t_philo *philo, char *str);

#endif
