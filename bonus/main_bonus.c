/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 13:31:09 by alsanche          #+#    #+#             */
/*   Updated: 2022/05/30 19:14:35 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_test(int fd, char *path, char **comand, char **enpv)
{
	dup2(fd, STDOUT_FILENO);
	execve(path, comand, enpv);
}

void	ft_romulo(int *fd, char **comand, t_s_comand *wolf)
{
	char	*gps;
	int		i;

	close(fd[FD_W]);
	dup2(fd[FD_R], STDIN_FILENO);
	i = 0;
	while (wolf->path[i])
	{
		gps = ft_strjoin(wolf->path[i], comand[0]);
		if (!access(gps, R_OK))
			ft_test(wolf->file_out, gps, comand, wolf->empv);
		free(gps);
		i++;
	}
	send_error(1, comand[0]);
	ft_free_all(wolf);
	close(fd[FD_R]);
	exit (-1);
}

void	ft_remo(int *fd, char **comand, t_s_comand *wolf)
{
	char	*gps;
	int		i;

	close(fd[FD_R]);
	dup2(wolf->file_in, STDIN_FILENO);
	close(wolf->file_in);
	i = 0;
	while (wolf->path[i])
	{
		gps = ft_strjoin(wolf->path[i], comand[0]);
		if (!access(gps, R_OK))
			ft_test(fd[FD_W], gps, comand, wolf->empv);
		free(gps);
		i++;
	}
	send_error(1, comand[0]);
	ft_free_all(wolf);
	close(fd[FD_W]);
	exit (-1);
}

void	pipex(t_s_comand *wolf, char **arv, char **enpv, int x)
{
	int		fd[2];

	wolf->path = find_path(enpv);
	wolf->empv = enpv;
	if (x == 0)
	{
		draw_command(wolf, arv);
		wolf->file_out = open(arv[wolf->arkc - 1],
				O_RDWR | O_CREAT | O_TRUNC, 0644);
	}
	if (wolf->file_out < 0)
		send_error(0, arv[wolf->arkc]);
	pipe(fd);
	init_childs(wolf, fd);
}

int	main(int arc, char **arv, char **enpv)
{
	t_s_comand	wolf;
	char		*temp;

	if (arc >= 5)
	{
		if (ft_strncmp(arv[1], "here_doc", 9) == 0)
			ft_here_doc(arv, enpv, &wolf);
		temp = arv[1];
		if (arv[1][0] != '/')
			temp = ft_strjoin("./", arv[1]);
		if (access(temp, F_OK))
		{
			send_error(3, arv[1]);
			free(temp);
			return (0);
		}
		wolf.file_in = open(arv[1], O_RDONLY, 0644);
		if (wolf.file_in < 0)
			send_error(0, arv[1]);
		wolf.arkc = arc;
		wolf.n_com = arc - 3;
		pipex(&wolf, arv, enpv, 0);
	}
	else
		send_error(2, "insufficient or too many arguments ");
	return (0);
}
