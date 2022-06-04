/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:01:55 by alsanche          #+#    #+#             */
/*   Updated: 2022/05/30 19:09:30 by alsanche         ###   ########lyon.fr   */
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
	wolf->file_in = open(".ninja.txt", O_RDWR | O_CREAT, 0644);
	if (wolf->file_in < 0)
		ft_putstr_fd("the ninja was discovered", 1);
	wolf->file_out = open(arv[5], O_RDWR | O_CREAT, 0644);
	if (wolf->file_out < 0)
		send_error(0, arv[5]);
	printf("estas aqui");
	wolf->command = malloc(sizeof(char**) * 3);
	wolf->n_com = 1;
	wolf->command[0] = ft_split(arv[3], ' ');
	wolf->command[1] = ft_split(arv[4], ' ');
	ft_take_msn(arv[2], wolf);
	pipex(wolf, arv, enpv, 1);
}
