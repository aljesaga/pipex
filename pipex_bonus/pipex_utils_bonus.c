/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 18:44:01 by alsanche          #+#    #+#             */
/*   Updated: 2022/05/25 15:48:01 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(const char *c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		i++;
	}
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	int		i;

	i = 0;
	if (!fd || !s)
		return ;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(1, "\n", 1);
}

void	draw_command(t_s_comand *wolf, char **arv)
{
	int	i;
	int x;

	i = 0;
	x = 2;
	wolf->command = malloc(sizeof(**char) * wolf->n_comand + 1);
	while (i < wolf->n_comand)
	{
		wolf->command[i] = ft_split(arv[x], ' ');
		i++;
		x++;
	}
}

ft_roma(int *fd, char **command)
{
	char	**path;
	char	*gps;
	int		i;

	dup2(fd[FD_R], STDIN_FILENO);
	path = find_path(enpv);
	i = 0;
	while (path[i])
	{
		gps = ft_strjoin(path[i], command[0]);
		if (!access(gps, R_OK))
			ft_test(fd[FD_W], gps, command, enpv);
		free(gps);
		i++;
	}
	send_error(1, comand);
	ft_free_all(command);
	ft_free_all(path);
	close(fd[FD_R]);
	close(fd[FD_w]);
	exit (-1);
}

void	init_childs(t_s_comand *wolf, int *fd, pid_t *child)
{	
	int	i;

	i = 0;
	while (i < wolf->n_com)
	{
		child[i] = fork();
		if (child[i] == -1)
			send_error(2, "fork");
		if (child[i] == 0)
			ft_remo(fd, wolf->file_in, wolf->command[i], enpv);
		else if (i >= 1 && i < wolf->n_com)
		{
			ft_roma(fd, wolf->command[i], enpv);
		}
		else
		{
			ft_romulo(fd, wolf->file_out, wolf->command[i], enpv);
		}
	wait(&child);
	close(file_out);
}
