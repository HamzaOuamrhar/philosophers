/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 02:06:02 by houamrha          #+#    #+#             */
/*   Updated: 2024/04/05 16:13:48 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	one_philo(t_data *data)
{
	data->philos[0].philo = fork();
	if (data->philos[0].philo == -1)
		return (0);
	if (data->philos[0].philo == 0)
	{
		printf("%ld %d has taken a fork\n", get_time() - data->start,
			data->philos[0].id);
		precise_usleep(data->t_die);
		printf("%ld %d died\n", get_time() - data->start, data->philos[0].id);
	}
	else
		wait(NULL);
	return (1);
}
