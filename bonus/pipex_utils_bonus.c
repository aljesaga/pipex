/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 18:44:01 by alsanche          #+#    #+#             */
/*   Updated: 2022/07/09 18:08:54 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
}

void	ft_take_msn(char *std, t_s_comand *wolf)
{
	char	*temp;
	int		len;

	len = ft_len(std);
	close (wolf->file_out);
	while (1)
	{
		ft_putstr_fd("pipex_alsanche heredoc> ", 1);
		temp = get_next_line(STDIN_FILENO);
		if (!temp)
		{
			close (wolf->file_in);
			exit (1);
		}
		if (!ft_strncmp(temp, std, len) && temp[len] == '\n')
		{
			close (wolf->file_in);
			free(temp);
			exit (0);
		}
		ft_putstr_fd(temp, wolf->file_in);
		free(temp);
	}
}

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
