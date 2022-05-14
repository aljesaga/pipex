/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 15:27:30 by alsanche          #+#    #+#             */
/*   Updated: 2021/08/15 17:22:05 by alsanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*aux;
	const char	*ax;

	i = 0;
	aux = dest;
	ax = src;
	if (aux == '\0' && ax == '\0')
		return (NULL);
	while (i < n)
	{
		aux[i] = ax[i];
		i++;
	}
	return (dest);
}
