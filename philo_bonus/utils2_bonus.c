/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 15:06:02 by houamrha          #+#    #+#             */
/*   Updated: 2024/04/05 16:14:45 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_for_die(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	while (1)
	{
		sem_wait(philo->edit_sem);
		if (get_time() - philo->last_meal_time > philo->data->t_die)
		{
			write_logs("died\n", philo, 1);
			sem_post(philo->edit_sem);
			return (NULL);
		}
		sem_post(philo->edit_sem);
	}
	return (NULL);
}

int	simulation(t_philo *philo)
{
	if (pthread_create(&philo->checker, NULL, &check_for_die, philo) != 0)
		return (0);
	if (pthread_detach(philo->checker) != 0)
		return (0);
	while (1)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (1);
}

void	eating(t_philo *philo)
{
	sem_wait(philo->data->forks);
	write_logs("has taken a fork\n", philo, 0);
	sem_wait(philo->data->forks);
	write_logs("has taken a fork\n", philo, 0);
	write_logs("is eating\n", philo, 0);
	sem_wait(philo->edit_sem);
	philo->last_meal_time = get_time();
	philo->meals_eaten += 1;
	if (philo->meals_eaten == philo->data->n_must_eat)
		sem_post(philo->data->full_sem);
	sem_post(philo->edit_sem);
	precise_usleep(philo->data->t_eat);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

void	sleeping(t_philo *philo)
{
	write_logs("is sleeping\n", philo, 0);
	precise_usleep(philo->data->t_sleep);
}

void	thinking(t_philo *philo)
{
	write_logs("is thinking\n", philo, 0);
}
