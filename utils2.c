/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 15:06:02 by houamrha          #+#    #+#             */
/*   Updated: 2024/03/29 00:22:58 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->fork);
	write_logs("taken", philo);

	pthread_mutex_lock(&philo->right_fork->fork);
	write_logs("taken", philo);

	pthread_mutex_lock(&philo->m_e_m);
	philo->last_meal_time = get_time();
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
