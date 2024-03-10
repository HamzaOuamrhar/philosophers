/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 23:14:14 by houamrha          #+#    #+#             */
/*   Updated: 2024/03/10 17:14:57 by houamrha         ###   ########.fr       */
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

int	ft_atoi(const char *str);
int	are_valide_args(int argc, char **argv);

#endif