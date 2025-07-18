/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 15:06:02 by houamrha          #+#    #+#             */
/*   Updated: 2024/03/31 01:02:28 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->fork);
	write_logs("has taken a fork\n", philo);
	pthread_mutex_lock(&philo->right_fork->fork);
	write_logs("has taken a fork\n", philo);
	pthread_mutex_lock(&philo->m_e_m);
	philo->last_meal_time = get_time();
	philo->meals_eaten += 1;
	pthread_mutex_lock(&philo->data->full_m);
	if (philo->meals_eaten == philo->data->n_must_eat)
		philo->data->all_full += 1;
	pthread_mutex_unlock(&philo->data->full_m);
	pthread_mutex_unlock(&philo->m_e_m);
	write_logs("is eating\n", philo);
	precise_usleep(philo->data->t_eat);
	pthread_mutex_unlock(&philo->right_fork->fork);
	pthread_mutex_unlock(&philo->left_fork->fork);
}

void	sleeping(t_philo *philo)
{
	write_logs("is sleeping\n", philo);
	precise_usleep(philo->data->t_sleep);
}

void	thinking(t_philo *philo)
{
	write_logs("is thinking\n", philo);
}

void	*thread_handler(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	while (1)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

void	destroy_mutexes(t_data *data)
{
	int	i;

	pthread_mutex_destroy(&data->full_m);
	pthread_mutex_destroy(&data->write_lock);
	i = 0;
	while (i < data->n_filo)
	{
		pthread_mutex_destroy(&data->philos[i].m_e_m);
		pthread_mutex_destroy(&data->forks[i].fork);
		i++;
	}
}
