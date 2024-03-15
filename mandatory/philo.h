/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 23:14:14 by houamrha          #+#    #+#             */
/*   Updated: 2024/03/15 15:13:20 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>

typedef struct t_philo
{
	pthread_t	philo;
	int			id;
	t_fork		*left_fork;
	t_fork		*right_fork;
}	t_philo;

typedef struct t_fork
{
	pthread_mutex_t	fork;
	int				id;
}	t_fork;

typedef struct t_data
{
	t_philo	philos[200];
	t_fork	forks[200];
	int	n_filo;
	int	n_forks;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	n_must_eat;
}	t_data;

int	ft_atoi(const char *str);
int	are_valide_args(int argc, char **argv);

#endif