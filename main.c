/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 13:31:09 by alsanche          #+#    #+#             */
/*   Updated: 2022/01/22 19:11:35 by alsanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_test(int fd, char *path, char **comand, char **enpv)
{
	dup2(fd, STDOUT_FILENO);
	execve(path, comand, enpv);
}

void ft_romulo(int *fd, int file, char **comand, char **enpv)
{
	char	**path;
	char	*gps;
	int		i;

	close(fd[FD_W]);
	dup2(fd[FD_R], STDIN_FILENO);
	path = find_path(enpv);
	i = 0;
	while(path[i])
	{
		gps = ft_strjoin(path[i], comand[0]);
		if (!access(gps, R_OK))
			ft_test(file, gps, comand, enpv);
		free(gps);
		i++;
	}
	send_error(1, comand[0]);
	ft_free_all(path);
	close(file);
	close(fd[FD_R]);
	exit (0);
}

void ft_remo(int *fd, int file, char **comand, char **enpv)
{
	char	**path;
	char	*gps;
	int		i;

	close(fd[FD_R]);
	dup2(file, STDIN_FILENO);
	close(file);
	path = find_path(enpv);
	i = 0;
	while(path[i])
	{
		gps = ft_strjoin(path[i], comand[0]);
		if (!access(gps, R_OK))
			ft_test(fd[FD_W], gps, comand, enpv);
		free(gps);
		i++;
	}
	send_error(1, comand[0]);
	ft_free_all(path);
	close(fd[FD_W]);
	exit (0);
}

void pipex(int *file, char **arv, char **enpv)
{
	int		fd[2];
	char	**remo;
	char	**romulo;
	pid_t	child;

	remo = ft_split(arv[2], ' ');
	romulo = ft_split(arv[3], ' ');
	pipe(fd);
	child = fork();
	if (child == -1)
			send_error(2, "fork");
	if (child == 0)
		ft_remo(fd, file[0], remo, enpv);
	else
		ft_romulo(fd, file[1], romulo, enpv);
}

int main(int arc, char **arv, char **enpv)
{
	int		file[2];

	if (arc == 5)
	{
		file[0] = open(arv[1], O_RDONLY);
		if (file[0] == -1)
		{
			send_error(0, arv[1]);
			return (0);
		}
		file[1] = open(arv[4], O_CREAT | O_WRONLY);
		if (file[1] == -1)
		{
			send_error(0, arv[4]);
			return (0);
		}
		pipex(file, arv, enpv);
	}
	else
		send_error(2, "insufficient arguments ");
	return (0);
}
