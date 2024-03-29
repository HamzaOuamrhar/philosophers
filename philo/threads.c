/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 23:51:44 by houamrha          #+#    #+#             */
/*   Updated: 2024/03/29 23:52:41 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&data->write_lock, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&data->full_m, NULL) != 0)
		return (0);
	while (i < data->n_filo)
	{
		if (pthread_mutex_init(&data->philos[i].m_e_m, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

void	assign_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_filo)
	{
		if ((i + 1) % 2 == 0)
		{
			data->philos[i].left_fork = &(data->forks[i]);
			data->philos[i].right_fork = &(data->forks[(i + 1) % data->n_filo]);
		}
		else
		{
			data->philos[i].left_fork = &(data->forks[(i + 1) % data->n_filo]);
			data->philos[i].right_fork = &(data->forks[i]);
		}
		i++;
	}
}

int	alive(t_philo *philo)
{
	pthread_mutex_lock(&philo->m_e_m);
	if (get_time() - philo->last_meal_time > philo->data->t_die)
	{
		pthread_mutex_lock(&philo->data->write_lock);
		printf("%ld %d died\n", get_time() - philo->data->start, philo->id);
		pthread_mutex_unlock(&philo->m_e_m);
		return (0);
	}
	pthread_mutex_unlock(&philo->m_e_m);
	return (1);
}

int	philo_full(t_philo *philo)
{
	pthread_mutex_lock(&philo->m_e_m);
	pthread_mutex_lock(&philo->data->full_m);
	if (philo->data->all_full != philo->data->n_filo)
	{
		pthread_mutex_unlock(&philo->data->full_m);
		pthread_mutex_unlock(&philo->m_e_m);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->full_m);
	pthread_mutex_unlock(&philo->m_e_m);
	pthread_mutex_lock(&philo->data->write_lock);
	return (1);
}

int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_forks)
	{
		data->forks[i].id = i;
		if (pthread_mutex_init(&data->forks[i].fork, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}
