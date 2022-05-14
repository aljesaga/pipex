/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 16:37:32 by alsanche          #+#    #+#             */
/*   Updated: 2021/08/24 13:17:24 by alsanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count(int n)
{
	int	count;

	count = 0;
	if (n == -2147483648)
		return (11);
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = -n;
		count++;
	}
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static int	ft_exp(int n)
{	
	int	i;
	int	top;

	i = 1;
	top = -1;
	if (n == -2147483648)
		return (1000000000);
	if (n < 0)
		n = -n;
	while ((n / i) > 9 && top++ < 10)
	{
		i *= 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int			j;
	long int	exp;
	char		*str;

	str = (char *)malloc(sizeof(char) * (count(n) + 1));
	if (!str)
		return (NULL);
	exp = ft_exp(n);
	j = 0;
	if (n < 0)
	{
		str[j] = 45;
		j++;
	}
	if (n > 0)
		n = -n;
	while (exp > 0)
	{
		str[j++] = -(n / exp % 10) + 48;
		exp /= 10;
	}
	str[j] = '\0';
	return (str);
}
