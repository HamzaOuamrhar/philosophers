/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 23:13:07 by houamrha          #+#    #+#             */
/*   Updated: 2024/04/02 22:51:14 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&data->write_lock, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&data->full_m, NULL) != 0)
		return (0);
	while (i < data->n_filo)
	{
		if (pthread_mutex_init(&data->philos[i].m_e_m, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	create_threads(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_filo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal_time = get_time();
		if (pthread_create(&data->philos[i].philo, NULL,
				&thread_handler, &data->philos[i]) != 0)
			return (0);
		if (pthread_detach(data->philos[i].philo) != 0)
			return (0);
	}
	while (1)
	{
		i = -1;
		while (++i < data->n_filo)
		{
			if (!alive(&data->philos[i]) || philo_full(&data->philos[i]))
				return (1);
		}
	}
	return (1);
}

int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_forks)
	{
		data->forks[i].id = i;
		if (pthread_mutex_init(&data->forks[i].fork, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	multiple_philos(t_data *data)
{
	data->start = get_time();
	data->all_full = 0;
	data->still = 1;
	if (!init_mutexes(data))
		return (0);
	if (!init_forks(data))
		return (0);
	assign_forks(data);
	if (!create_threads(data))
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (printf("Number of arguments not valide!\n"), 1);
	if (!parse(argc, argv, &data))
		return (printf("Some arguments arn't valide!\n"), 1);
	if (data.n_filo == 1)
	{
		if (!one_philo(&data))
			return (printf("Error\n"), 1);
		else
			return (0);
	}
	else
	{
		if ((!multiple_philos(&data)))
			return (printf("Error!\n"), 1);
	}
	destroy_mutexes(&data);
	return (0);
}
