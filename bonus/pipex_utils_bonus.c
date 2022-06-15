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
	wolf->command = malloc(sizeof(char **) * wolf->n_com + 1);
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

	dup2(fd[FD_R], STDIN_FILENO);
	i = 0;
	printf("fd[R]-----%d\n", fd[FD_R]);//aqui
	printf("fd[W]-----%d\n", fd[FD_W]);//aqui
	printf("estoy ejecutando-----%s\n", command[0]);//AQUI
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

pid_t	init_childs(t_s_comand *wolf, char **cmd, int *fd, int i)
{	
	pid_t	child;
	int j = 0;//AQUI
	int fd2[2];

	child = fork();
	pipe(fd2);
	fd[0] = 0;
	while (cmd[j] && child > 0)//AQUI
	{
		printf("%s\n", cmd[j]);
		j++;
	}//AQUI
	printf("%d\n", child);//AQUI
	if (child == -1)
		send_error(2, "fork");
	if (child > 0 && i == 0)
		ft_remo(fd2, cmd, wolf);
	else if (child > 0)
	{
		ft_roma(fd2, cmd, wolf);
	}
	return (child);
}
