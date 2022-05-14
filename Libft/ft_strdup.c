/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 15:29:06 by alsanche          #+#    #+#             */
/*   Updated: 2021/08/12 15:29:06 by alsanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		t;
	char	*s2;

	t = ft_strlen(s1);
	s2 = (char *)malloc(t + 1);
	if (!s2)
		return (NULL);
	ft_memcpy(s2, s1, t);
	s2[t] = '\0';
	return (s2);
}
