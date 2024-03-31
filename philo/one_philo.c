/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 02:06:02 by houamrha          #+#    #+#             */
/*   Updated: 2024/03/31 15:31:33 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*one_philo_handler(void *p)
{
	t_data	*data;
	long	start;

	data = (t_data *)p;
	start = get_time();
	printf("%ld 1 has taken a fork\n", get_time() - start);
	while (1)
	{
		if (get_time() - start > data->t_die)
		{
			printf("%ld 1 died\n", get_time() - start);
			break ;
		}
	}
	return (NULL);
}

int	one_philo(t_data *data)
{
	data->philos[0].id = 1;
	if (pthread_create(&data->philos[0].philo, NULL,
			&one_philo_handler, data) != 0)
		return (0);
	if (pthread_join(data->philos[0].philo, NULL) != 0)
		return (0);
	return (1);
}
