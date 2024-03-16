/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 23:14:20 by houamrha          #+#    #+#             */
/*   Updated: 2024/03/16 00:55:52 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

long	get_time()
{
	struct timeval t_time;
	long			time;

	if (gettimeofday(&t_time, NULL))
		return (0);
	time = (t_time.tv_sec * 1000) + (t_time.tv_usec / 1000);
	return (time);
}

void	usleep_fnc(long mls)
{
	long	start;

	start = get_time();
	while (get_time() - start < mls)
		usleep(100);
}