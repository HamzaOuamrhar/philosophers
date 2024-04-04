/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houamrha <houamrha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:47:57 by houamrha          #+#    #+#             */
/*   Updated: 2024/04/04 11:23:21 by houamrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

char	*ft_strdup(const char *s1)
{
	char		*copy;
	char		*c;
	const char	*s;
	int			i;

	i = 0;
	s = s1;
	while (*s)
	{
		i++;
		s++;
	}
	copy = (char *)malloc(i * sizeof(char) + 1);
	if (copy == NULL)
		return (0);
	c = copy;
	while (*s1)
	{
		*c = *s1;
		c++;
		s1++;
	}
	*c = '\0';
	return (copy);
}

static int	int_len(int n)
{
	int	i;
	int	nb;

	i = 0;
	if (n < 0)
		nb = -n;
	else
		nb = n;
	while (nb > 0)
	{
		nb /= 10;
		i++;
	}
	if (n < 0)
		i += 1;
	return (i);
}

char	*ft_itoa(int n)
{
	char			*str;
	int				j;
	int				i;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	i = int_len(n);
	j = i;
	str = (char *)malloc((i + 1) * sizeof(char));
	if (str == 0)
		return (0);
	if (n < 0)
		str[0] = '-';
	if (n < 0)
		n = -n;
	while (n > 0)
	{
		str[i - 1] = (n % 10) + 48;
		n /= 10;
		i--;
	}
	str[j] = '\0';
	return (str);
}
