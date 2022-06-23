/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:01:55 by alsanche          #+#    #+#             */
/*   Updated: 2022/06/23 12:24:15 by alsanche         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_free_c(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
		i++;
	while (i--)
	{
		free(str[i]);
	}
	free(str);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*c2;
	unsigned char	*c1;

	i = 0;
	c1 = (unsigned char *) s1;
	c2 = (unsigned char *) s2;
	while (*c1 != '\0' && *c2 != '\0' && i < n)
	{
		if ((*c1 <= 0 || *c1 == 127) || (*c2 <= 0 || *c2 >= 127))
			return ('\0');
		if (*c1 != *c2)
			return (*c1 - *c2);
		i++;
		c1++;
		c2++;
	}
	if (i != n)
	{
		return (*c1 - *c2);
	}
	return (0);
}

void	ft_take_msn(char *std, t_s_comand *wolf)
{
	char	*temp;
	char	*limit;

	limit = ft_strjoin(std, "\n");
	while (1)
	{
		temp = get_next_line(STDIN_FILENO);
		if (ft_strncmp(temp, limit, ft_strlen(limit) + 1) == 0)
		{	
			free(temp);
			free(limit);
			break ;
		}
		ft_putstr_fd(temp, wolf->file_in);
		free(temp);
	}
}

void	ft_here_doc(char **arv, char **enpv, t_s_comand *wolf)
{
	char	*del[2];

	del[0] = "rm";
	del[1] = " .ninja.txt";
	wolf->file_in = open("./.ninja.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (wolf->file_in < 0)
		ft_putstr_fd("the ninja was discovered", 1);
	ft_take_msn(arv[2], wolf);
	wolf->n_com = wolf->ar - 4;
	pipex(wolf, arv, enpv, 3);
	close(wolf->file_in);
	execve("/usr/bin/rm", del, enpv);
}

void	ft_multi_cmd(int arc, char **arv, char **enpv, t_s_comand *wolf)
{
	char	*temp;

	temp = arv[1];
	if (arv[1][0] != '/')
	{	
		temp = ft_strjoin("./", arv[1]);
		if (access(temp, F_OK))
		{
			send_error(3, arv[1]);
			free(temp);
			exit (0);
		}
		free(temp);
	}
	wolf->file_in = open(arv[1], O_RDONLY, 0644);
	if (wolf->file_in < 0)
		send_error(0, arv[1]);
	wolf->n_com = arc - 3;
	pipex(wolf, arv, enpv, 2);
}
