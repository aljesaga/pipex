/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 18:44:01 by alsanche          #+#    #+#             */
/*   Updated: 2022/06/15 21:52:32 by alsanche         ###   ########lyon.fr   */
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

void	ft_roma(int *fd, char **command, t_s_comand *wolf)
{
	char	*gps;
	int		i;

	i = 0;
	dup2(fd[FD_R], STDIN_FILENO);
	printf("std --------> %d\n", STDIN_FILENO);
	printf("fd[R]-----%d\n", fd[FD_R]);//aqui
	printf("fd[W]-----%d\n", fd[FD_W]);//aqui
	printf("ROMA ejecutando-----%s\n", command[0]);//AQUI
	while (wolf->path[i])
	{
		gps = ft_strjoin(wolf->path[i], command[0]);
		if (!access(gps, X_OK))
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

void	init_childs(t_s_comand *wolf, char **cmd, int *fd, int i)
{	
	wolf->childs = fork();
	printf("%d\n", wolf->childs);//AQUI
	if (wolf->childs == -1)
		send_error(2, "fork");
	if (wolf->childs > 0 && i == 0)
		ft_remo(fd, cmd, wolf);
	else if (wolf->childs > 0 && i + 1 == wolf->n_com)
		ft_romulo(fd, wolf->command[i], wolf);
	else if (wolf->childs > 0)
		ft_roma(fd, cmd, wolf);
}
