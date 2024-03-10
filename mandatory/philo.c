/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 23:13:07 by houamrha          #+#    #+#             */
/*   Updated: 2024/03/10 12:30:30 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse(int argc, char **argv, t_philo *philo)
{
	if (!are_valide_args(argc, argv))
		return (0);
	philo->n_filo = ft_atoi(argv[1]);
	philo->n_forks = philo->n_filo;
	philo->t_die = ft_atoi(argv[2]);
	philo->t_eat = ft_atoi(argv[3]);
	philo->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		philo->n_must_eat = ft_atoi(argv[5]);
		if (!philo->n_must_eat)
			return (0);
	}
	if (!philo->n_filo || philo->n_filo > 200 || philo->t_die < 60
		|| philo->t_eat < 60
		|| philo->t_sleep < 60)
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_philo	philo;

	if (argc < 5 || argc > 6)
	{
		printf("Number of arguments not valide!\n");
		return (1);
	}
	if (!parse(argc, argv, &philo))
	{
		printf("Some arguments arn't valide!\n");
		return (1);
	}
}
