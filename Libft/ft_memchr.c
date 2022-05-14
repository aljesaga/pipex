/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 13:18:51 by alsanche          #+#    #+#             */
/*   Updated: 2021/08/12 13:18:51 by alsanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, int n)
{
	const char	*str;
	int			i;

	str = s;
	i = 0;
	while (i < n)
	{
		if (*str == (char)c)
			return ((char *) str);
		i++;
		str++;
	}
	if (c == '\0')
		return (NULL);
	return (NULL);
}
