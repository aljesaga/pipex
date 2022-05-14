/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 15:34:57 by alsanche          #+#    #+#             */
/*   Updated: 2021/08/31 15:54:06 by alsanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	chekchr(char c, char const *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s2;
	int		init;
	int		end;
	int		i;

	init = 0;
	if (!s1 || !set)
		return (NULL);
	while (chekchr(s1[init], set) && s1[init])
		init++;
	end = ft_strlen(s1);
	while (chekchr(s1[end - 1], set) && (end > init))
		end--;
	s2 = (char *)malloc(end - init + 1);
	if (!s2)
		return (NULL);
	i = 0;
	while (init < end)
	{
		s2[i] = s1[init];
		i++;
		init++;
	}
	s2[i] = '\0';
	return (s2);
}
