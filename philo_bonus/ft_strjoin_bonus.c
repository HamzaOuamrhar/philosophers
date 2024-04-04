/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:11:21 by houamrha          #+#    #+#             */
/*   Updated: 2024/04/04 11:59:51 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_strlen(char const *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join_string;
	char	*join;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	join_string = (char *)malloc
		((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (join_string == 0)
		return (0);
	join = join_string;
	while (*s1)
	{
		*join = *s1;
		join++;
		s1++;
	}
	while (*s2)
	{
		*join = *s2;
		join++;
		s2++;
	}
	*join = '\0';
	return (join_string);
}
