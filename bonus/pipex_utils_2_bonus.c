/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:01:55 by alsanche          #+#    #+#             */
/*   Updated: 2022/07/09 17:42:00 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*c2;
	unsigned char	*c1;

	i = 0;
	c1 = (unsigned char *) s1;
	c2 = (unsigned char *) s2;
	while (*c1 != '\0' && *c2 != '\0' && i < n)
	{
		if ((*c1 <= 0 || *c1 == 127) || (*c2 <= 0 || *c2 >= 127))
			return ('\0');
		if (*c1 != *c2)
			return (*c1 - *c2);
		i++;
		c1++;
		c2++;
	}
	if (i != n)
	{
		return (*c1 - *c2);
	}
	return (0);
}

char	*str_path(char **enpv)
{
	int	i;

	i = 0;
	if (!enpv || *enpv == NULL)
		return (NULL);
	while (enpv[i])
	{
		if (enpv[i][0] == 'P' && enpv[i][1] == 'A'
			&& enpv[i][2] == 'T' && enpv[i][3] == 'H')
			return (enpv[i]);
		i++;
	}
	return (NULL);
}

char	**find_path(char **enpv)
{
	char	**gps;
	char	*path;
	char	*aux;
	int		i;

	path = str_path(enpv);
	if (!path)
		return (NULL);
	i = -1;
	gps = ft_split(path, ':');
	while (gps[++i])
	{
		aux = gps[i];
		gps[i] = ft_strjoin(aux, "/");
		free(aux);
	}
	return (gps);
}

void	selec_out_file(t_s_comand *wolf, char *arv)
{
	if (wolf->here_doc == 1)
		wolf->file_out = open(arv, O_RDWR | O_CREAT | O_APPEND, 0644);
	else
		wolf->file_out = open(arv, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (wolf->file_out < 0)
		send_error(0, arv);
}
