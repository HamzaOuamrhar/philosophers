/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:36:44 by houamrha          #+#    #+#             */
/*   Updated: 2024/03/23 00:44:22 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data	t_data;

struct s_data
{
	int		n_filo;
	int		n_forks;
	int		t_die;
	int		t_eat;
	int		t_sleep;
	int		n_must_eat;
};

int		ft_atoi(const char *str);
int		are_valide_args(int argc, char **argv);
long	get_time(void);
void	precise_usleep(long mls);
int		ft_strcmp(char *s1, char *s2);
void	*thread_handler(void *p);
int		parse(int argc, char **argv, t_data *data);

#endif