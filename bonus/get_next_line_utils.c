/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 13:14:32 by alsanche          #+#    #+#             */
/*   Updated: 2021/09/26 13:14:35 by alsanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

size_t	ft_len(const char *c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		i++;
	}
	return (i);
}

char	*ft_join(char const *s1, char const *s2, size_t c)
{
	char	*new;
	int		i;
	int		j;
	int		size;

	if (!s1 || !s2)
		return (NULL);
	size = (ft_len(s1) + (int)c);
	new = (char *)malloc(sizeof(char) * size + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		new[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < (int)c)
	{
		new[i++] = s2[j];
		j++;
	}
	new[i++] = '\0';
	return (new);
}

char	*ft_strup(char *s1, size_t i)
{
	size_t	t;
	char	*s2;

	t = 0;
	s2 = (char *)malloc(sizeof(char) * (i + 1));
	if (!s2)
		return (NULL);
	while (t < i)
	{
		s2[t] = s1[t];
		t++;
	}
	s2[t] = '\0';
	return (s2);
}

size_t	ft_check(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			i++;
			return (i);
		}
		i++;
	}
	return (i);
}

char	*ft_remove(char *str, size_t i)
{
	size_t	next;

	next = 0;
	while (str[i] != '\0')
	{
		str[next] = str[i];
		i++;
		next++;
	}
	str[next] = '\0';
	return (str);
}
