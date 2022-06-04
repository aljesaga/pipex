/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 12:34:57 by alsanche          #+#    #+#             */
/*   Updated: 2021/09/30 14:30:24 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	ft_verify(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_read(int fd, char *buf, char *str)
{
	char	*aux;
	ssize_t	c;

	if (!str)
		str = ft_strup("", 0);
	c = read(fd, buf, BUFFER_SIZE);
	while (c != 0)
	{
		aux = str;
		str = ft_join(aux, buf, c);
		free(aux);
		if (ft_verify(str) == 1)
			break ;
		c = read(fd, buf, BUFFER_SIZE);
	}
	return (str);
}

char	*get_next_line(int fd)
{
	char		*out;
	char		*buf;
	static char	*str;
	ssize_t		c;

	buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	if (read(fd, buf, 0) == -1 || BUFFER_SIZE < 1 || fd < 0)
	{
		free(buf);
		return (NULL);
	}
	str = ft_read(fd, buf, str);
	free(buf);
	c = ft_check(str);
	if (c < 1)
	{
		free(str);
		str = (NULL);
		return (NULL);
	}
	out = ft_strup(str, c);
	str = ft_remove(str, c);
	return (out);
}
