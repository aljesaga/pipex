/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 15:32:50 by alsanche          #+#    #+#             */
/*   Updated: 2021/08/27 15:48:51 by alsanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	d;
	size_t	s;
	size_t	f;
	size_t	i;

	i = 0;
	d = ft_strlen(dst);
	s = ft_strlen(src);
	if (size <= d || size == 0)
		return (s + size);
	f = size - d - 1;
	while (f-- > 0 && src[i] != '\0')
	{
		dst[d + i] = src[i];
		i++;
	}
	dst[d + i] = '\0';
	return (d + s);
}
