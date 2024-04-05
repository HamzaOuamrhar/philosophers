/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 23:14:14 by houamrha          #+#    #+#             */
/*   Updated: 2024/04/05 02:29:24 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <semaphore.h>
# include <stdlib.h>
# include <signal.h>

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
	sem_t			*edit_sem;
};

struct s_data
{
	t_philo			philos[200];
	pthread_t		full_checker;
	int				n_filo;
	int				n_forks;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_must_eat;
	long			start;
	sem_t			*write_sem;
	sem_t			*end_sem;
	sem_t			*forks;
	sem_t			*full_sem;
};

int		ft_atoi(const char *str);
int		are_valide_args(int argc, char **argv);
long	get_time(void);
void	precise_usleep(long mls);
int		ft_strcmp(char *s1, char *s2);
void	write_logs(char *s, t_philo *philo, int flag);
void	thinking(t_philo *philo);
void	sleeping(t_philo *philo);
void	eating(t_philo *philo);
int		parse(int argc, char **argv, t_data *data);
int		one_philo(t_data *data);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_itoa(int n);
int		simulation(t_philo *philo);

#endif