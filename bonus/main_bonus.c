/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 13:31:09 by alsanche          #+#    #+#             */
/*   Updated: 2022/07/09 18:31:23 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	init_childs(t_s_comand *wolf, char **cmd, int i, char *arv)
{	
	pid_t	pid;
	int		fd[2];

	pipe(fd);
	pid = fork();
	if (pid != 0)
		wolf->childs[i] = pid;
	else if (pid == -1)
		send_error(2, "fork");
	else
	{
		if (i + 1 == wolf->n_com)
		{	
			selec_out_file(wolf, arv);
		}
		else
			wolf->file_out = fd[FD_W];
		ft_run(fd, cmd, wolf);
	}
	close(fd[FD_W]);
	close(wolf->file_in);
	wolf->file_in = fd[FD_R];
}

void	pipex(t_s_comand *wolf, char **arv, char **enpv, int x)
{
	int	i;
	int	status;

	wolf->path = find_path(enpv);
	wolf->empv = enpv;
	draw_command(wolf, arv, x);
	wolf->childs = malloc(sizeof(pid_t *) * wolf->n_com);
	if (!wolf->childs)
		send_error(0, "children not found");
	i = -1;
	while (++i < wolf->n_com)
		init_childs(wolf, wolf->command[i], i, arv[wolf->ar - 1]);
	i = -1;
	while (++i < wolf->n_com)
		waitpid(wolf->childs[i], &status, 0);
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
	ft_free_all(wolf);
}

void	ft_here_doc(char **arv, char **enpv, t_s_comand *wolf)
{	
	int		here[2];
	pid_t	child;

	pipe(here);
	child = fork();
	if (child < 0 || here[FD_R] < 0)
		send_error(2, "here_doc");
	wolf->file_in = here[FD_W];
	wolf->file_out = here[FD_R];
	if (child == 0)
	{
		ft_take_msn(arv[2], wolf);
	}
	else
	{
		waitpid(child, NULL, 0);
		close(here[FD_W]);
		wolf->file_in = here[FD_R];
		wolf->n_com = wolf->ar - 4;
		wolf->here_doc = 1;
		pipex(wolf, arv, enpv, 3);
	}
}

void	ft_multi_cmd(int arc, char **arv, char **enpv, t_s_comand *wolf)
{
	char	*temp;

	temp = arv[1];
	if (temp[0] != '/')
		temp = ft_strjoin("./", arv[1]);
	if (access(temp, F_OK))
	{
		send_error(3, arv[1]);
		free(temp);
	}
	wolf->file_in = open(arv[1], O_RDONLY, 0644);
	if (wolf->file_in < 0)
		wolf->file_in = open(".ninja.txt", O_RDONLY | O_CREAT, 0644);
	wolf->n_com = arc - 3;
	unlink(".ninja.txt");
	wolf->here_doc = 0;
	pipex(wolf, arv, enpv, 2);
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
	{
		send_error(2, "insufficient or too many arguments ");
		return (1);
	}
	return (0);
}
