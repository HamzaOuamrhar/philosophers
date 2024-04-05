/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 23:14:20 by houamrha          #+#    #+#             */
/*   Updated: 2024/04/05 01:18:35 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	are_valide_args(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

long	get_time(void)
{
	struct timeval	t_time;
	long			time;

	if (gettimeofday(&t_time, NULL))
		return (0);
	time = (t_time.tv_sec * 1000) + (t_time.tv_usec / 1000);
	return (time);
}

void	precise_usleep(long mls)
{
	long	start;

	start = get_time();
	while (get_time() - start < mls)
		usleep(100);
}

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
	else
		data->n_must_eat = 1000000;
	if (!data->n_filo || data->n_filo > 200 || data->t_die < 60
		|| data->t_eat < 60
		|| data->t_sleep < 60)
		return (0);
	return (1);
}

void	write_logs(char *s, t_philo *philo, int flag)
{
	long	timestamp;

	timestamp = get_time() - philo->data->start;
	sem_wait(philo->data->write_sem);
	printf("%ld %d %s", timestamp, philo->id, s);
	if (flag == 1)
	{
		sem_post(philo->data->end_sem);
		sem_post(philo->data->write_sem);
		return ;
	}
	sem_post(philo->data->write_sem);
}
