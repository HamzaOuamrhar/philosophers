/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 23:13:07 by houamrha          #+#    #+#             */
/*   Updated: 2024/03/16 14:18:05 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse(int argc, char **argv, t_data *data)
{
	if (!are_valide_args(argc, argv))
		return (0);
	data->n_filo = ft_atoi(argv[1]);
	data->n_forks = data->n_filo;
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		data->n_must_eat = ft_atoi(argv[5]);
		if (!data->n_must_eat)
			return (0);
	}
	if (!data->n_filo || data->n_filo > 200 || data->t_die < 60
		|| data->t_eat < 60
		|| data->t_sleep < 60)
		return (0);
	return (1);
}

void	*thread_handler(void *p)
{
	t_philo *philo = (t_philo *)p;
	while (!philo->data->ready)
	;
	printf("%d\n", philo->id);
	return (NULL);
}

int	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_filo)
	{
		data->philos[i].id = i + 1;
		if (pthread_create(&(data->philos[i].philo), NULL, &thread_handler, &(data->philos[i])) != 0)
			return (0);
		i++;
	}
	data->ready = 1;
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

	data->ready = 0;
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
	if (!init(&data))
	{
		printf("Thread error!\n");
		return (1);
	}
	return (0);
}
