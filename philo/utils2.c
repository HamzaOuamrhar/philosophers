/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 15:06:02 by houamrha          #+#    #+#             */
/*   Updated: 2024/03/24 21:18:28 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	all_full(t_data *data)
{
	int i = 0;
	while (i < data->n_filo)
	{
		if (!data->philos[i].full)
			return (0);
		i++;
	}
	return (1);
}

void	set_value(int *val, pthread_mutex_t data_lock, int value)
{
	pthread_mutex_lock(&data_lock);
	*val = value;
	pthread_mutex_unlock(&data_lock);
}

int	get_value(int val, pthread_mutex_t data_lock)
{
	int	value;

	pthread_mutex_lock(&data_lock);
	value = val;
	pthread_mutex_unlock(&data_lock);
	return (value);
}