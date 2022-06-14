/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 13:31:09 by alsanche          #+#    #+#             */
/*   Updated: 2022/06/14 20:26:45 by alsanche         ###   ########lyon.fr   */
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
		if (!access(gps, X_OK))
			ft_test(wolf->file_out, gps, comand, wolf->empv);
		free(gps);
		i++;
	}
	send_error(1, comand[0]);
	//ft_free_all(wolf);
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
		if (!access(gps, X_OK))
			ft_test(fd[FD_W], gps, comand, wolf->empv);
		free(gps);
		i++;
	}
	send_error(1, comand[0]);
	//ft_free_all(wolf);
	close(fd[FD_W]);
	exit (-1);
}

void	pipex(t_s_comand *wolf, char **arv, char **enpv, int x)
{
	int		i;
	int		fd[2];

	wolf->path = find_path(enpv);
	wolf->empv = enpv;
	pipe(fd);
	draw_command(wolf, arv, x);
	wolf->file_out = open(arv[wolf->ar - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (wolf->file_out < 0)
		send_error(0, arv[wolf->ar]);
	i = 0;
	while (i < wolf->n_com - 1)
	{
		init_childs(wolf, fd, i);
		i++;
	}
	ft_romulo(fd, wolf->command[i], wolf);
}

int	main(int arc, char **arv, char **enpv)
{
	t_s_comand	wolf;

	if (arc > 4)
	{
		wolf.ar = arc;
		if (ft_strncmp(arv[1], "here_doc", 9) == 0)
			ft_here_doc(arv, enpv, &wolf);
		else
			ft_multi_cmd(arc, arv, enpv, &wolf);
	}
	else
		send_error(2, "insufficient or too many arguments ");
	return (0);
}
