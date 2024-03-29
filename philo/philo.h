/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 23:14:14 by houamrha          #+#    #+#             */
/*   Updated: 2024/03/24 23:18:04 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo	t_philo;
typedef struct s_data	t_data;
typedef struct s_fork	t_fork;

struct s_fork
{
	pthread_mutex_t	fork;
	int				id;
};

struct s_philo
{
	pthread_t	philo;
	int			id;
	t_fork		*left_fork;
	t_fork		*right_fork;
	t_data		*data;
	int			meals_eaten;
	long		last_meal_time;
	int			full;
	pthread_mutex_t	edit_lock;
};

struct s_data
{
	t_philo	philos[200];
	t_fork	forks[200];
	int		n_filo;
	int		n_forks;
	int		t_die;
	int		t_eat;
	int		t_sleep;
	int		n_must_eat;
	int		ready;
	int		end;
	long	start;
	pthread_mutex_t	data_lock;
	pthread_mutex_t	write_lock;
};

int		ft_atoi(const char *str);
int		are_valide_args(int argc, char **argv);
long	get_time(void);
void	precise_usleep(long mls);
int		ft_strcmp(char *s1, char *s2);
void	write_logs(char *s, t_philo *philo);
void	*thread_handler(void *p);
void	thinking(t_philo *philo);
void	sleeping(t_philo *philo);
void	eating(t_philo *philo);
int		parse(int argc, char **argv, t_data *data);
int		one_philo(t_data *data);
int		all_full(t_data *data);
void	set_value(int *val, pthread_mutex_t data_lock, int value);
int		get_value(int val, pthread_mutex_t data_lock);
void	set_l_m_t(long *val, pthread_mutex_t data_lock, long value);

#endif