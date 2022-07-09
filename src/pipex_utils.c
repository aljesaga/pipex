/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 18:44:01 by alsanche          #+#    #+#             */
/*   Updated: 2022/07/09 18:18:34 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_test(int fd, char *path, char **comand, char **enpv)
{
	dup2(fd, STDOUT_FILENO);
	execve(path, comand, enpv);
}

void	ft_run(int *fd, char **comand, t_s_comand *wolf)
{
	char	*gps;
	int		i;

	close(fd[FD_R]);
	dup2(wolf->file_in, STDIN_FILENO);
	close(wolf->file_in);
	i = 0;
	if (!access(comand[0], X_OK))
		ft_test(wolf->file_out, comand[0], comand, wolf->empv);
	while (wolf->path != NULL && wolf->path[i])
	{
		gps = ft_strjoin(wolf->path[i], comand[0]);
		if (!access(gps, X_OK))
			ft_test(wolf->file_out, gps, comand, wolf->empv);
		free(gps);
		i++;
	}
	if (wolf->path == NULL)
		send_error(3, comand[0]);
	else
		send_error(1, comand[0]);
	ft_free_all(wolf);
	close(fd[FD_W]);
	exit (127);
}

void	draw_command(t_s_comand *wolf, char **arv, int x)
{
	int	i;

	i = 0;
	wolf->command = malloc(sizeof(char **) * wolf->n_com + 2);
	if (!wolf->command)
		send_error(3, "no funciono el malloc");
	while (i < wolf->n_com)
	{
		wolf->command[i] = ft_split(arv[x], ' ');
		i++;
		x++;
	}
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
