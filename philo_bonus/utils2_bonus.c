/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 15:06:02 by houamrha          #+#    #+#             */
/*   Updated: 2024/04/04 11:02:36 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eating(t_philo *philo)
{
	write_logs("has taken a fork\n", philo);
	write_logs("has taken a fork\n", philo);
	philo->last_meal_time = get_time();
	philo->meals_eaten += 1;
	write_logs("is eating\n", philo);
	precise_usleep(philo->data->t_eat);
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
