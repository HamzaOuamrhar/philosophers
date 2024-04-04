/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 23:13:07 by houamrha          #+#    #+#             */
/*   Updated: 2024/04/04 11:05:31 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	multiple_philos(t_data *data)
{
	(void)data;
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
	return (0);
}
