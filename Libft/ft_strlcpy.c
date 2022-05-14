/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 15:32:57 by alsanche          #+#    #+#             */
/*   Updated: 2021/08/28 22:04:33 by alsanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	if (!src || !dst || size < 0)
		return (0);
	i = ft_strlen(src);
	j = 0;
	if (i + 1 < size)
	{
		while (j < i + 1)
		{
			dst[j] = src[j];
			j++;
		}
	}
	else if (size != 0)
	{
		while (j < size - 1)
		{
			dst[j] = src[j];
			j++;
		}
		dst[size - 1] = '\0';
	}
	return (i);
}
