/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 15:06:02 by houamrha          #+#    #+#             */
/*   Updated: 2024/03/28 00:44:57 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->fork);
	write_logs("taken", philo);

	pthread_mutex_lock(&philo->right_fork->fork);
	write_logs("taken", philo);

	pthread_mutex_lock(&philo->l_m_t_m);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->l_m_t_m);

	pthread_mutex_lock(&philo->m_e_m);
	philo->meals_eaten += 1;
	pthread_mutex_unlock(&philo->m_e_m);

	write_logs("eating", philo);

	precise_usleep(philo->data->t_eat);

	pthread_mutex_unlock(&philo->right_fork->fork);
	pthread_mutex_unlock(&philo->left_fork->fork);
}

void	sleeping(t_philo *philo)
{
	write_logs("sleeping", philo);
	precise_usleep(philo->data->t_sleep);
}

void	thinking(t_philo *philo)
{
	write_logs("thinking", philo);
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

int	get_value(int value, pthread_mutex_t mutex)
{
	int	val;

	pthread_mutex_lock(&mutex);
	val = value;
	pthread_mutex_unlock(&mutex);
	return (val);
}
