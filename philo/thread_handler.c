/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:37:11 by houamrha          #+#    #+#             */
/*   Updated: 2024/03/24 23:41:25 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork->fork);
	write_logs("taken", philo);
	pthread_mutex_lock(&philo->left_fork->fork);
	write_logs("taken", philo);
	write_logs("eating", philo);
	set_l_m_t(&philo->last_meal_time, philo->edit_lock, get_time());
	philo->meals_eaten += 1;
	precise_usleep(philo->data->t_eat);
	if (philo->meals_eaten == philo->data->n_must_eat)
		set_value(&philo->full, philo->edit_lock, 1);
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
	while (!get_value(philo->data->ready, philo->data->data_lock))
		;
	while (!get_value(philo->data->end, philo->data->data_lock))
	{
		if (philo->full)
			break ;
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
