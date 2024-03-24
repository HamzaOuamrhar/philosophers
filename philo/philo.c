/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 23:13:07 by houamrha          #+#    #+#             */
/*   Updated: 2024/03/24 21:21:32 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_for_die(t_data *data)
{
	int	i;

	while (!data->end && !all_full(data))
	{
		i = 0;
		while (!data->end && i < data->n_filo)
		{
			if ((data->philos[i].meals_eaten != 0
					&& (get_time()
						- data->philos[i].last_meal_time > data->t_die)
							&& data->philos[i].meals_eaten != data->n_must_eat)
				|| (data->philos[i].meals_eaten == 0
					&& (get_time() - data->start > data->t_die)))
			{
				printf("[%ld] %d died\n", (get_time() - data->start),
					data->philos[i].id);
				data->end = 1;
			}
			i++;
		}
	}
}

int	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_filo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].full = 0;
		data->philos[i].meals_eaten = 0;
		if (pthread_create(&(data->philos[i].philo), NULL, &thread_handler,
				&(data->philos[i])) != 0)
			return (0);
		i++;
	}
	set_value(&data->ready, data->data_lock, 1);
	data->start = get_time();
	check_for_die(data);
	i = 0;
	while (i < data->n_filo)
	{
		if (pthread_join(data->philos[i].philo, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	init_data(t_data *data)
{
	int	i;

	pthread_mutex_init(&data->data_lock, NULL);
	data->ready = 0;
	data->end = 0;
	i = 0;
	while (i < data->n_filo)
	{
		data->philos[i].data = data;
		if ((i + 1) % 2 == 0)
		{
			data->philos[i].left_fork = &(data->forks[i]);
			data->philos[i].right_fork = &(data->forks[(i + 1) % data->n_filo]);
		}
		else
		{
			data->philos[i].left_fork = &(data->forks[(i + 1) % data->n_filo]);
			data->philos[i].right_fork = &(data->forks[i]);
		}
		i++;
	}
	if (!init_philos(data))
		return (0);
	return (1);
}

int	init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_forks)
	{
		data->forks[i].id = i;
		if (pthread_mutex_init(&(data->forks[i].fork), NULL) != 0)
			return (0);
		i++;
	}
	if (!init_data(data))
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
	{
		printf("Number of arguments not valide!\n");
		return (1);
	}
	if (!parse(argc, argv, &data))
	{
		printf("Some arguments arn't valide!\n");
		return (1);
	}
	if (data.n_filo == 1)
	{
		if (!one_philo(&data))
		{
			printf("Error\n");
			return (1);
		}
	}
	else
	{
		if ((!init(&data)))
		{
			printf("Error!\n");
			return (1);
		}
	}
	return (0);
}
