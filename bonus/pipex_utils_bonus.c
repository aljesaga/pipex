/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 18:44:01 by alsanche          #+#    #+#             */
/*   Updated: 2022/05/30 15:51:11 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
	int	x;

	i = 0;
	x = 2;
	wolf->command = malloc(sizeof(char**) * wolf->n_com + 1);
	while (i < wolf->n_com)
	{
		wolf->command[i] = ft_split(arv[x], ' ');
		i++;
		x++;
	}
}

void	ft_roma(int *fd, char **command, t_s_comand *wolf)
{
	char	*gps;
	int		i;

	dup2(fd[FD_R], STDIN_FILENO);
	i = 0;
	while (wolf->path[i])
	{
		gps = ft_strjoin(wolf->path[i], command[0]);
		if (!access(gps, R_OK))
			ft_test(fd[FD_W], gps, command, wolf->empv);
		free(gps);
		i++;
	}
	send_error(1, command[0]);
	ft_free_all(wolf);
	close(fd[FD_R]);
	close(fd[FD_W]);
	exit (-1);
}

void	init_childs(t_s_comand *wolf, int *fd)
{	
	int		i;
	pid_t	child;

	i = 0;
	while (i < wolf->n_com)
	{
		child = fork();
		if (child == -1)
			send_error(2, "fork");
		if (child == 0 && i == 0)
			ft_remo(fd, wolf->command[i], wolf);
		else if (child == 0)
		{
			ft_roma(fd, wolf->command[i], wolf);
		}
		else
		{
			ft_romulo(fd, wolf->command[i], wolf);
		}
	}
	wait(&child);
	close(wolf->file_out);
}
