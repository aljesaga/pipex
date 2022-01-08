/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 13:31:09 by alsanche          #+#    #+#             */
/*   Updated: 2022/01/06 13:05:09 by alsanche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int arc, char **arv)
{
	int		fd[2];
	int		file;
	pid_t	pid_c;
	pid_t	pid_c2;
	char	*ls[] = {"ls", "-la","/home/alsanche/pipex", 0};
	char	*wc[] = {"wc", "-l", 0};
	char	*enpv[] = {"PATH=/bin", 0};

	arv[1] = NULL;
	if (arc >= 5)
	{
		pipe(fd);
		pid_c = fork();
		if (pid_c == 0)
		{
			close(fd[FD_R]);
			dup2(fd[FD_W], STDOUT_FILENO);
			close(fd[1]);
			execve("usr/bin/ls", ls, enpv);
			exit (0);
		}
		else
		{
			close(fd[FD_W]);
			pid_c2 = fork();
			if (pid_c2 == 0)
			{
				file = open(arv[4], O_WRONLY);
				dup2(fd[FD_R], STDIN_FILENO);
				close(fd[FD_R]);
				dup2(file, STDOUT_FILENO);
				execve("usr/bin/wc", wc, enpv);
				close(fd[1]);
			}
			else
				close (fd[FD_R]);
		}
	}
	return (0);
}

/*{
	int	fd;

	if (arg >= 5)
	{
		
		fork()
		
	}
	return (0);	
}*/
