/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 13:31:09 by alsanche          #+#    #+#             */
/*   Updated: 2022/05/25 16:25:20 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_test(int fd, char *path, char **comand, char **enpv)
{
	dup2(fd, STDOUT_FILENO);
	execve(path, comand, enpv);
}

void	ft_romulo(int *fd, int file, char *comand, char **enpv)
{
	char	**romulo;
	char	**path;
	char	*gps;
	int		i;

	close(fd[FD_W]);
	dup2(fd[FD_R], STDIN_FILENO);
	romulo = ft_split(comand, ' ');
	path = find_path(enpv);
	i = 0;
	while (path[i])
	{
		gps = ft_strjoin(path[i], romulo[0]);
		if (!access(gps, R_OK))
			ft_test(file, gps, romulo, enpv);
		free(gps);
		i++;
	}
	send_error(1, comand);
	ft_free_all(romulo);
	ft_free_all(path);
	close(fd[FD_R]);
	exit (-1);
}

void	ft_remo(int *fd, int file, char *comand, char **enpv)
{
	char	**remo;
	char	**path;
	char	*gps;
	int		i;

	close(fd[FD_R]);
	dup2(file, STDIN_FILENO);
	close(file);
	remo = ft_split(comand, ' ');
	path = find_path(enpv);
	i = 0;
	while (path[i])
	{
		gps = ft_strjoin(path[i], remo[0]);
		if (!access(gps, R_OK))
			ft_test(fd[FD_W], gps, remo, enpv);
		free(gps);
		i++;
	}
	send_error(1, comand);
	ft_free_all(remo);
	ft_free_all(path);
	close(fd[FD_W]);
	exit (-1);
}

void	pipex(int *file, char **arv, char **enpv)
{
	int		fd[2];
	pid_t	child;

	file[0] = open(arv[1], O_RDONLY, 0644);
	if (file[0] < 0)
		send_error(0, arv[1]);
	file[1] = open(arv[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (file[1] < 0)
		send_error(0, arv[4]);
	pipe(fd);
	child = fork();
	if (child == -1)
		send_error(2, "fork");
	if (child == 0)
		ft_remo(fd, file[0], arv[2], enpv);
	else
	{
		ft_romulo(fd, file[1], arv[3], enpv);
	}
	wait(&child);
	close(file[1]);
}

int	main(int arc, char **arv, char **enpv)
{
	int		file[2];
	char	*temp;

	if (arc == 5)
	{
		temp = arv[1];
		if (arv[1][0] != '/')
			temp = ft_strjoin("./", arv[1]);
		if (access(temp, F_OK))
		{
			send_error(3, arv[1]);
			free(temp);
			return (0);
		}
		pipex(file, arv, enpv);
	}
	else
		send_error(2, "insufficient or too many arguments ");
	return (0);
}
