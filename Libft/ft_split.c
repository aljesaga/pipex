/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 16:59:59 by alsanche          #+#    #+#             */
/*   Updated: 2021/08/31 15:33:05 by alsanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	chars(char const *s, char c, size_t l)
{
	size_t	car;

	car = 0;
	while (s[l] != '\0' && s[l++] != c)
		car++;
	return (car);
}

static size_t	count(char const *s, char c)
{
	size_t	col;
	size_t	i;

	col = 0;
	i = -1;
	if (s[0] && s[0] != c)
		col = 1;
	while (s[++i] != '\0')
		if (s[i] == c && (s[i + 1] != c && s[i + 1]))
			col++;
	return (col);
}

static char	**ft_free(char **str, size_t space)
{
	while (space-- > 0)
		free(str[space]);
	free(str);
	return (NULL);
}

static char	*ft_word(char const *s, char c, char *str, size_t i)
{
	size_t	k;

	k = 0;
	while (s[i] != '\0' && s[i] != c)
		str[k++] = s[i++];
	str[k] = '\0';
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	size_t	i;
	size_t	space;
	size_t	num;

	space = -1;
	i = 0;
	if (!s)
		return (NULL);
	str = (char **)malloc(sizeof(char *) * (count(s, c) + 1));
	if (str == NULL)
		return (NULL);
	while (++space < (count(s, c)))
	{
		while (s[i] && s[i] == c)
			i++;
		num = chars(s, c, i);
		str[space] = (char *)malloc(sizeof(char) * (num + 1));
		if (str[space] == NULL)
			return (ft_free(str, space));
		str[space] = ft_word(s, c, str[space], i);
		i += num;
	}
	str[space] = 0;
	return (str);
}
