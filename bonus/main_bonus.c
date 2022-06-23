/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 13:31:09 by alsanche          #+#    #+#             */
/*   Updated: 2022/06/23 15:26:33 by alsanche         ###   ########lyon.fr   */
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
	dup2(wolf->file_in, STDIN_FILENO);
	close(wolf->file_in);
	printf("std --------> %d\n", STDIN_FILENO);
	printf("fd[R]-----%d\n", wolf->file_in);//aqui
	printf("fd[W]-----%d\n", wolf->file_out);//aqui
	printf("final ejecutando---%s\n", comand[0]);//AQUI
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
	printf("std --------> %d\n", STDIN_FILENO);
	printf("fd[R]-----%d\n", wolf->file_in);//aqui
	printf("fd[W]-----%d\n", fd[FD_W]);//aqui
	printf("estoy ejecutando---%s\n", comand[0]);//aqui
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
	ft_free_all(wolf);
	close(fd[FD_W]);
	exit (-1);
}
/*1 | 2 | 3

(10, 11) = pipe()
hijo 1: in(file_in), out(11)
hijo 1: close(10)
padre close(11)
(12, 13) = pipe()
2: in(10), out(13)
3: in(12), out(file_out)*/

void	pipex(t_s_comand *wolf, char **arv, char **enpv, int x)
{
	int		i;

	wolf->path = find_path(enpv);
	wolf->empv = enpv;
	i = -1;
	draw_command(wolf, arv, x);
	wolf->file_out = open(arv[wolf->ar - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (wolf->file_out < 0)
		send_error(0, arv[wolf->ar]);
	wolf->childs = malloc(sizeof(pid_t *) * wolf->n_com);
	if (!wolf->childs)
		send_error(0, "no de crean los hijos");
	i = -1;
	while (++i < wolf->n_com)
		init_childs(wolf, wolf->command[i], i);
	i = -1;
	while (++i < wolf->n_com)
		waitpid(wolf->childs[i], NULL, 0);
	ft_free_all(wolf);
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
