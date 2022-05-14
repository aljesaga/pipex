/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanhe <alsanche@student.42madrid.es>      +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 21:24:50 by alsanche          #+#    #+#             */
/*   Updated: 2021/08/01 21:24:50 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check(char *c, char *c2, size_t j, size_t n)
{
	int	i;

	i = 0;
	while (c2[i] && j <= n)
	{
		if (c[i] != c2[i] || j >= n)
			return (0);
		i++;
		j++;
	}
	return (1);
}

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t		len;
	size_t		j;

	len = ft_strlen(s2);
	if (s1 == '\0')
		j = 2147483647 * s1[0];
	if ((!s2 || len == 0) || (s1 == s2))
		return ((char *)s1);
	if ((n - 1 < 0) || (len > n))
		return (NULL);
	else
	{
		j = 0;
		while (j < n && s1[j])
		{
			if (s1[j] == s2[0])
				if (check((char *)&s1[j], (char *)&s2[0], j, n) != 0)
					return ((char *)&s1[j]);
			j++;
		}
	}
	return (NULL);
}
