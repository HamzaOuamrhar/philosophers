/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 23:14:14 by houamrha          #+#    #+#             */
/*   Updated: 2024/03/12 14:05:04 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>

typedef struct t_philo
{
	pthread_t th[200];
	pthread_mutex_t	mutex;
	int	n_filo;
	int	n_forks;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	n_must_eat;
}	t_philo;

typedef struct t_philo_data
{
	t_philo	*philo;
	int		index;
}	t_philo_data;

int	ft_atoi(const char *str);
int	are_valide_args(int argc, char **argv);

#endif