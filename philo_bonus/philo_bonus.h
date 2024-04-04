/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 23:14:14 by houamrha          #+#    #+#             */
/*   Updated: 2024/04/04 11:29:49 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <semaphore.h>

typedef struct s_philo	t_philo;
typedef struct s_data	t_data;

struct s_philo
{
	pid_t			philo;
	pthread_t		checker;
	int				id;
	t_data			*data;
	int				meals_eaten;
	long			last_meal_time;
	sem_t			edit_sem;
};

struct s_data
{
	t_philo			philos[200];
	int				n_filo;
	int				n_forks;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_must_eat;
	long			start;
	sem_t			die_sem;
	sem_t			write_sem;
	sem_t			full_sem;
};

int		ft_atoi(const char *str);
int		are_valide_args(int argc, char **argv);
long	get_time(void);
void	precise_usleep(long mls);
int		ft_strcmp(char *s1, char *s2);
void	write_logs(char *s, t_philo *philo);
void	thinking(t_philo *philo);
void	sleeping(t_philo *philo);
void	eating(t_philo *philo);
int		parse(int argc, char **argv, t_data *data);
int		one_philo(t_data *data);

#endif