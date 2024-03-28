/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 23:13:07 by houamrha          #+#    #+#             */
/*   Updated: 2024/03/28 00:32:12 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutexes(t_data *data)
{
	int	i = 0;

	if (pthread_mutex_init(&data->write_lock, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&data->edit_lock, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&data->all_full_m, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&data->die_m, NULL) != 0)
		return (0);
	while (i < data->n_filo)
	{
		if (pthread_mutex_init(&data->philos[i].m_e_m, NULL) != 0)
			return (0);
		if (pthread_mutex_init(&data->philos[i].l_m_t_m, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

void	assign_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_filo)
	{
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
}

void	check_for_die(t_data *data)
{
	int	i;

	while (!get_value(data->die, data->die_m))
	{
		i = 0;
		while (!get_value(data->die, data->die_m) && i < data->n_filo)
		{
			pthread_mutex_lock(&data->philos[i].l_m_t_m);
			pthread_mutex_lock(&data->philos[i].m_e_m);
			if ((get_time() - data->philos[i].last_meal_time > data->t_die && data->philos[i].meals_eaten != 0)
			|| (get_time() - data->start > data->t_die && data->philos[i].meals_eaten == 0))
			{
				write_logs("die", &data->philos[i]);
				pthread_mutex_lock(&data->write_lock);
				pthread_mutex_lock(&data->die_m);
				data->die = 1;
				pthread_mutex_unlock(&data->die_m);
				pthread_mutex_unlock(&data->philos[i].l_m_t_m);
				pthread_mutex_unlock(&data->philos[i].m_e_m);
				break ;
			}
			pthread_mutex_unlock(&data->philos[i].m_e_m);
			pthread_mutex_unlock(&data->philos[i].l_m_t_m);
			i++;
		}
	}
}

int	philos_alive(t_philo *philo){
	long	t;

	pthread_mutex_lock(&philo->l_m_t_m);
	t = get_time() - philo->last_meal_time;
	pthread_mutex_unlock(&philo->l_m_t_m);
	if (t > philo->data->t_die)
	{
		pthread_mutex_lock(&philo->data->write_lock);
		printf("%ld %d died\n",
			get_time() - philo->data->start, philo->id);
		return (0);
	}
	return (1);
}

int philos_full(t_data *data)
{
	int i = 0;
	while (i < data->n_filo)
	{
		pthread_mutex_lock(&data->philos[i].m_e_m);
		if (data->philos[i].meals_eaten < data->n_must_eat)
		{
			pthread_mutex_unlock(&data->philos[i].m_e_m);
			return (0);
		}
		pthread_mutex_unlock(&data->philos[i].m_e_m);
		i++;
	}
	pthread_mutex_lock(&data->write_lock);
	return (1);
}

void detach(t_data *data)
{
	pthread_mutex_unlock(&data->write_lock);
	int i = 0;
	while (i < data->n_filo)
	{
		pthread_detach(data->philos[i].philo);
		i++;
	}
}

int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_filo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal_time = 0;
		if (pthread_create(&data->philos[i].philo, NULL, &thread_handler, &data->philos[i]) != 0)
			return (0);
		i++;
	}
	while (1)
	{
		i = 0;
		while (i < data->n_filo)
		{
			if (!philos_alive(&data->philos[i]) || philos_full(data))
			{
				detach(data);
				return (1);
			}
			i++;
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
	data->ready = 0;
	data->all_full = 0;
	data->die = 0;
	data->start = get_time();
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
		if ((!multiple_philos(&data)))
		{
			printf("Error!\n");
			return (1);
		}
	}
	return (0);
}
