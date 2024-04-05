/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 00:25:07 by houamrha          #+#    #+#             */
/*   Updated: 2024/04/05 16:30:08 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	kill_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_filo)
	{
		if (data->philos[i].philo != 0)
			kill(data->philos[i].philo, SIGINT);
		i++;
	}
}

void	close_sem(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_filo)
		sem_close(data->philos[i].edit_sem);
	sem_close(data->end_sem);
	sem_close(data->full_sem);
	sem_close(data->write_sem);
	sem_close(data->forks);
}
