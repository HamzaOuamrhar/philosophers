/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 15:06:02 by houamrha          #+#    #+#             */
/*   Updated: 2024/04/04 22:20:52 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	simulation(t_philo *philo)
{
	while (1)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
}

void	eating(t_philo *philo)
{
	sem_wait(philo->data->forks);
	write_logs("has taken a fork\n", philo);
	sem_wait(philo->data->forks);
	write_logs("has taken a fork\n", philo);
	sem_wait(philo->edit_sem);
	philo->last_meal_time = get_time();
	philo->meals_eaten += 1;
	sem_post(philo->edit_sem);
	write_logs("is eating\n", philo);
	precise_usleep(philo->data->t_eat);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
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
