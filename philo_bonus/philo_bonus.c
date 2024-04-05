/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 23:13:07 by houamrha          #+#    #+#             */
/*   Updated: 2024/04/05 16:15:02 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*full_check(void *p)
{
	t_data	*data;
	int		i;

	i = 0;
	data = (t_data *)p;
	while (i <= data->n_filo)
	{
		sem_wait(data->full_sem);
		i++;
	}
	sem_post(data->end_sem);
	return (NULL);
}

int	multiple_philos(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_filo)
	{
		data->philos[i].philo = fork();
		if (data->philos[i].philo == -1)
			return (0);
		if (data->philos[i].philo == 0)
			if (!simulation(&data->philos[i]))
				return (0);
	}
	if (pthread_create(&data->full_checker, NULL, &full_check, data) != 0)
		return (0);
	if (pthread_detach(data->full_checker) != 0)
		return (0);
	sem_wait(data->end_sem);
	kill_all(data);
	exit(0);
}

int	init_philos(t_data *data)
{
	int		i;
	char	*str;
	char	*nbr;

	i = -1;
	while (++i < data->n_filo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		data->philos[i].last_meal_time = get_time();
		data->philos[i].meals_eaten = 0;
		nbr = ft_itoa(data->philos[i].id);
		str = ft_strjoin("/sem", nbr);
		sem_unlink(str);
		data->philos[i].edit_sem = sem_open(str, O_CREAT, 0777, 1);
		if (data->philos[i].edit_sem == SEM_FAILED)
			return (free(nbr), free(str), 0);
		free(nbr);
		free(str);
	}
	return (1);
}

int	init_data(t_data *data)
{
	sem_unlink("/write_sem");
	sem_unlink("/end_sem");
	sem_unlink("/forks");
	sem_unlink("/full_sem");
	data->end_sem = sem_open("/end_sem", O_CREAT, 0777, 0);
	data->write_sem = sem_open("/write_sem", O_CREAT, 0777, 1);
	data->full_sem = sem_open("/full_sem", O_CREAT, 0777, 1);
	data->forks = sem_open("/forks", O_CREAT, 0777, data->n_filo);
	if (data->end_sem == SEM_FAILED || data->write_sem == SEM_FAILED
		|| data->forks == SEM_FAILED || data->full_sem == SEM_FAILED)
		return (0);
	data->start = get_time();
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (printf("Number of arguments not valide!\n"), 1);
	if (!parse(argc, argv, &data))
		return (printf("Some arguments arn't valide!\n"), 1);
	if (!init_philos(&data))
		return (printf("Error initializing philos\n"), 1);
	if (!init_data(&data))
		return (printf("Error initializing data\n"), 1);
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
	return (0);
}
